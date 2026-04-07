#include "System.h"


const char* Course_Names[] = {
    "Invalid",
    "Math",
    "Physics",
    "Operating Systems",
    "Computer Architecture",
    "Database",
    "C Programming",
    "Embedded C",
    "Data Structures",
    "IoT",
    "Artificial Intelligence"
};


/**
 * @brief  Initializes the student management system.
 *
 * @details
 * - Creates the database file if it does not exist.
 * - Prepares the system for file-based operations.
 *
 * @return F_OK if initialization succeeds, otherwise error code.
 */
F_Return_t System_Init(void) {
    
    FILE* fptr = NULL;

    /*
     * Open the main database file in append + binary mode.
     * - Creates the file if it does not exist.
     * - Does NOT erase existing data if the file already exists.
     */
    fptr = fopen("Students_Information.db", "ab+");

    /* Check if file opening failed */
    if (fptr == NULL)
    {
        /* Failed to create or open database file */
        return F_FILE_OPEN_ERROR;
    }

    /*
     * Close the database file.
     * At this point, the database file is guaranteed to exist.
     */
    fclose(fptr);

    /* System initialized successfully */
    return F_OK;

}

/* Helper function to check if ID exists in DB */
static F_Return_t Is_ID_In_DB(uint32_t id)
{
    FILE* fp = fopen("Students_Information.db", "rb");
    if (!fp) {
        printf("Database file not found!\n");
        return F_NOT_OK;
    }

    Student_t temp;
    while (fread(&temp, sizeof(Student_t), 1, fp) == 1)
    {
       // printf("Checking ID: %u\n", temp.id); // Debug print
        if (temp.id == id && temp.is_active) {
            fclose(fp);
            return F_OK;
        }
    }

    fclose(fp);
    return F_ID_NOT_FOUND;
}


/**
 * @brief  Imports student records from an external text file.
 *
 * @details
 * - Reads student data line by line from the specified file.
 * - Validates each record and prevents duplicate IDs.
 * - Ensures no student exceeds MAX_COURSES by asking user input if needed.
 * - Stores students with at least one course into the binary database.
 *
 * @param  import_file Path to the external input file.
 * @return F_OK if all records processed successfully, otherwise error code.
 */
F_Return_t Add_Student_From_File(const char* import_file)
{
    if (!import_file) 
    {
        return F_NOT_OK;
    }
    FILE* import_fp = fopen(import_file, "r");
    if (!import_fp) 
    {
        return F_FILE_OPEN_ERROR;
    }
    FILE* db_fp = fopen("Students_Information.db", "ab+"); // append + read
    if (!db_fp)
    {
        fclose(import_fp);
        return F_FILE_OPEN_ERROR;
    }

    char line[512];
    Student_t student;
    F_Return_t status = F_OK;

    while (fgets(line, sizeof(line), import_fp))
    {
        my_memset(&student, 0, sizeof(Student_t));
        student.is_active = 1;

        uint8_t duplicate_id = 0;
        uint8_t invalid_courses_flag = 0;
        uint8_t course_count_mismatch = 0;

        uint32_t expected_courses = 0;
        uint32_t valid_courses_count = 0;

        /* ---------- Parse ID ---------- */
        char* token = my_strtok(line, ",");
        if (!token) continue;
        student.id = (uint32_t)atoi(token);

        /* ---------- Check Duplicate ID ---------- */
        rewind(db_fp);
        Student_t tmp;
        while (fread(&tmp, sizeof(Student_t), 1, db_fp) == 1)
        {
            if (tmp.id == student.id && tmp.is_active)
            {
                duplicate_id = 1;
                break;
            }
        }

        /* ---------- First Name ---------- */
        token = my_strtok(NULL, ",");
        if (!token) continue;
        my_strncpy(student.first_name, token, sizeof(student.first_name) - 1);

        /* ---------- Last Name ---------- */
        token = my_strtok(NULL, ",");
        if (!token) continue;
        my_strncpy(student.last_name, token, sizeof(student.last_name) - 1);

        /* ---------- GPA ---------- */
        token = my_strtok(NULL, ",");
        if (!token) continue;
        student.GPA = atof(token);
        if (student.GPA < 0.0f || student.GPA > 4.0f)
        {
            printf("Invalid GPA %.2f for student ID %u\n", student.GPA, student.id);
            continue;
        }

        /* ---------- Expected Course Count ---------- */
        token = my_strtok(NULL, ",");
        if (!token) continue;
        expected_courses = (uint32_t)atoi(token);
        if (expected_courses == 0 || expected_courses > MAX_COURSES)
        {
            printf("Invalid expected course count %u for student ID %u\n", expected_courses, student.id);
            continue;
        }

        /* ---------- Courses ---------- */
        while ((token = my_strtok(NULL, ",")) != NULL)
        {
            uint32_t course_id = (uint32_t)atoi(token);

            /* Skip invalid range */
            if (course_id < 1 || course_id > MAX_COURSE_ID)
            {
                printf("Invalid course ID %u for student ID %u\n", course_id, student.id);
                invalid_courses_flag = 1;
                continue;
            }

            /* Skip duplicate course in this student */
            int duplicate = 0;
            for (int i = 0; i < valid_courses_count; i++)
            {
                if (student.courses[i] == course_id)
                {
                    duplicate = 1;
                    break;
                }
            }
            if (duplicate)
            {
                printf("Duplicate course %u for student ID %u\n", course_id, student.id);
                invalid_courses_flag = 1;
                continue;
            }

            /* Add course if valid */
            if (valid_courses_count < MAX_COURSES)
            {
                student.courses[valid_courses_count++] = course_id;
            }
            else
            {
                printf("Too many courses for student ID %u (max %d)\n", student.id, MAX_COURSES);
                invalid_courses_flag = 1;
            }
        }

        student.course_count = valid_courses_count;

        /* ---------- Final Validation ---------- */
        if (duplicate_id || invalid_courses_flag || student.course_count != expected_courses)
        {
            printf("Skipping student ID %u due to errors:\n", student.id);
            if (duplicate_id) printf("  - Duplicate ID in DB\n");
            if (invalid_courses_flag) printf("  - Invalid courses detected\n");
            if (student.course_count != expected_courses) printf("  - Course count mismatch (expected %u, got %u)\n", expected_courses, student.course_count);
            continue;
        }

        /* ---------- Write Valid Student ---------- */
        fwrite(&student, sizeof(Student_t), 1, db_fp);
    }

    fclose(import_fp);
    fclose(db_fp);

    printf("Student import completed.\n");
    return status;
}


/**
 * @brief  Adds a single student to the database using a given Student_t structure.
 *
 * @details
 * - Checks if the student ID already exists in the database.
 * - Appends the student record to the binary database file if valid.
 *
 * @param  student Pointer to the student structure to add.
 * @return F_OK if student is added successfully, or error code.
 */
F_Return_t Add_Student_Manually(const Student_t* student)
{
    if (!student)
        return F_NOT_OK;

    /* Open main database file in append binary mode */
    FILE* db_fp = fopen("Students_Information.db", "ab");
    if (!db_fp)
        return F_FILE_OPEN_ERROR;

    /* Check if ID already exists */

    FILE* check_fp = fopen("Students_Information.db", "rb");
    if (!check_fp)
    {
        fclose(db_fp);
        return F_FILE_OPEN_ERROR;
    }

    Student_t temp;
    while (fread(&temp, sizeof(Student_t), 1, check_fp) == 1)
    {
        if (temp.id == student->id && temp.is_active)
        {
            fclose(check_fp);
            fclose(db_fp);
            return F_ID_ALREADY_EXISTS;
        }
    }
    fclose(check_fp);

    /* Append new student to database */
    fwrite(student, sizeof(Student_t), 1, db_fp);
    fclose(db_fp);

    return F_OK;
}

/**
 * @brief  Searches for a student using their unique ID.
 *
 * @details
 * - Scans the database file record by record.
 * - Returns the student data if found.
 *
 * @param  id      Student unique ID.
 * @param  student Pointer to store the found student data.
 * @return F_OK if student is found, otherwise F_ID_NOT_FOUND.
 */
F_Return_t Find_Student_By_ID(uint32_t id, Student_t* student) {
    if (!student)
        return F_NOT_OK;

    /* Open database file in read binary mode */
    FILE* db_fp = fopen("Students_Information.db", "rb");
    if (!db_fp)
        return F_FILE_OPEN_ERROR;

    Student_t temp;
    while (fread(&temp, sizeof(Student_t), 1, db_fp) == 1)
    {
        /* Check for matching ID and active student */
        if (temp.id == id && temp.is_active)
        {
            *student = temp;  /* Copy data to output */
            fclose(db_fp);
            return F_OK;
        }
    }

    fclose(db_fp);
    return F_ID_NOT_FOUND;

}
//  ************** Helper function to print students details********************
/**
 * @brief  Prints a single student record to the console.
 *
 * @param  student Pointer to the student struct to print.
 */
void Print_Student(const Student_t* student)
{
    if (!student || !student->is_active)
        return;
    printf("\n");
    printf("\n=============================================================================================================\n");
    printf("ID             : %d\n", student->id);
    printf("Name           : %s %s\n", student->first_name, student->last_name);
    printf("GPA            : %.2f\n", student->GPA);

    printf("Courses IDs    : ");
    for (uint32_t i = 0; i < student->course_count; i++)
    {
        printf("%d ", student->courses[i]);
    }

    printf("\nCourses Names  : ");
    for (uint32_t i = 0; i < student->course_count; i++)
    {
        uint32_t cid = student->courses[i];
        if (cid < sizeof(Course_Names) / sizeof(Course_Names[0]))
            printf("%s, ", Course_Names[cid]);
        else
            printf("Unknown, ");
    }

    printf("\n=============================================================================================================\n");
}
/**
 * @brief  Searches for students using their first name.
 *
 * @details
 * - Compares the given name with database records.
 * - Displays all matching students.
 *
 * @param  fname First name to search for.
 * @return F_OK if at least one student is found.
 */
F_Return_t Find_Student_By_First_Name(const char* fname) {
    if (!fname)
        return F_NOT_OK;

    FILE* db_fp = fopen("Students_Information.db", "rb");
    if (!db_fp)
        return F_FILE_OPEN_ERROR;

    Student_t temp;
    F_Return_t found = F_ID_NOT_FOUND;

    while (fread(&temp, sizeof(Student_t), 1, db_fp) == 1)
    {
        if (temp.is_active && my_memcmp(temp.first_name, fname,my_strlen(fname)) == 0)
        {
            Print_Student(&temp);  /* Print matching student */
            found = F_OK;          /* Mark that at least one student is found */
        }
    }

    fclose(db_fp);
    return found;
 
}

/**
 * @brief  Retrieves all students registered in a specific course.
 *
 * @details
 * - Iterates through database records.
 * - Displays students enrolled in the given course.
 *
 * @param  course Course identifier.
 * @return F_OK if students are found, otherwise F_COURSE_NOT_FOUND.
 */
F_Return_t Get_Students_By_Course(Course_t course) {
    FILE* db_fp = fopen("Students_Information.db", "rb");
    if (!db_fp)
        return F_FILE_OPEN_ERROR;

    Student_t student;
    uint8_t found = 0;

    while (fread(&student, sizeof(Student_t), 1, db_fp) == 1)
    {
        if (!student.is_active)
            continue;

        for (uint32_t i = 0; i < student.course_count; i++)
        {
            if (student.courses[i] ==(uint8_t)course)
            {
                Print_Student(&student);
                found = 1;
                break;   
            }
        }
    }

    fclose(db_fp);

    return (found) ? F_OK : F_COURSE_NOT_FOUND;

}

/**
 * @brief  Updates an existing student record.
 *
 * @details
 * - Searches for the student by ID.
 * - Updates the student information in the database.
 * - Rewrites the database file to preserve consistency.
 *
 * @param  id Student unique ID.
 * @return F_OK if update succeeds, otherwise error code.
 */
F_Return_t Update_Student(uint32_t id) {
    FILE* db_fp = fopen("Students_Information.db", "rb");
    if (!db_fp)
        return F_FILE_OPEN_ERROR;

    FILE* temp_fp = fopen("Temp.db", "wb");
    if (!temp_fp)
    {
        fclose(db_fp);
        return F_FILE_OPEN_ERROR;
    }

    Student_t temp;
    F_Return_t found = F_ID_NOT_FOUND;

    while (fread(&temp, sizeof(Student_t), 1, db_fp) == 1)
    {
        if (temp.id == id && temp.is_active)
        {
            found = F_OK;
            char input[100];

            printf("\nUpdating Student ID: %u\n", id);
            printf("Leave field unchanged by entering 0 or empty.\n");

            /* ---------- First Name ---------- */
            printf("Current First Name: %s\nEnter new First Name: ", temp.first_name);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0; // remove newline
            if (my_strlen(input) > 0 && my_memcmp(input, "0",my_strlen(input)) != 0)
                strncpy(temp.first_name, input, sizeof(temp.first_name) - 1);

            /* ---------- Last Name ---------- */
            printf("Current Last Name: %s\nEnter new Last Name: ", temp.last_name);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            if (strlen(input) > 0 && my_memcmp(input, "0", my_strlen(input)) != 0)
                my_strncpy(temp.last_name, input, sizeof(temp.last_name) - 1);

            /* ---------- GPA ---------- */
            printf("Current GPA: %.2f\nEnter new GPA: ", temp.GPA);
            fgets(input, sizeof(input), stdin);
            input[my_strcspn(input, "\n")] = 0;
            if (my_strlen(input) > 0 && my_memcmp(input, "0", my_strlen(input)) != 0)
            {
                float gpa_val = atof(input);
                if (gpa_val >= 0.0f && gpa_val <= 4.0f)
                    temp.GPA = gpa_val;
                else
                    printf("Invalid GPA! Keeping previous value.\n");
            }

            /* ---------- Courses ---------- */
            printf("Current Courses (%d): ", temp.course_count);
            for (int i = 0; i < temp.course_count; i++)
                printf("%u ", temp.courses[i]);
            printf("\nEnter number of new courses : ");
            fgets(input, sizeof(input), stdin);
            input[my_strcspn(input, "\n")] = 0;
            if (my_strlen(input) > 0 && my_memcmp(input, "0", my_strlen(input)) != 0)
            {
                int new_count = atoi(input);
                if (new_count > 0 && new_count <= MAX_COURSES)
                {
                    temp.course_count = new_count;
                    for (int i = 0; i < new_count; i++)
                    {
                        while (1)
                        {
                            printf("Enter course %d (1-%d): ", i + 1, MAX_COURSES);
                            fgets(input, sizeof(input), stdin);
                            int cid = atoi(input);
                            if (cid >= 1 && cid <= MAX_COURSES)
                            {
                                temp.courses[i] = cid;
                                break;
                            }
                            else
                            {
                                printf("Invalid Course ID. Try again.\n");
                            }
                        }
                    }
                }
                else
                {
                    printf("Invalid number of courses. Keeping old courses.\n");
                }
            }

            printf("Student ID %u updated successfully.\n", id);
        }

        /* ---------- Write record to temp file ---------- */
        if (fwrite(&temp, sizeof(Student_t), 1, temp_fp) != 1)
        {
            fclose(db_fp);
            fclose(temp_fp);
            return F_NOT_OK;
        }
    }

    fclose(db_fp);
    fclose(temp_fp);

    /* Replace original DB if updated */
    if (found == F_OK)
    {
        remove("Students_Information.db");
        if (rename("Temp.db", "Students_Information.db") != 0)
            return F_NOT_OK;
    }
    else
    {
        remove("Temp.db");
    }

    return found;

}

/**
 * @brief  Deletes a student record from the database.
 *
 * @details
 * - Performs a logical delete by setting is_active flag.
 * - Preserves database integrity.
 *
 * @param  id Student unique ID.
 * @return F_OK if deletion succeeds.
 */
F_Return_t Delete_Student(uint32_t id) {
    FILE* db_fp = fopen("Students_Information.db", "rb");
    if (!db_fp)
        return F_FILE_OPEN_ERROR;

    FILE* temp_fp = fopen("Temp.db", "wb");
    if (!temp_fp)
    {
        fclose(db_fp);
        return F_FILE_OPEN_ERROR;
    }

    Student_t temp;
    F_Return_t found = F_ID_NOT_FOUND;

    while (fread(&temp, sizeof(Student_t), 1, db_fp) == 1)
    {
        if (temp.id == id && temp.is_active)
        {
            temp.is_active = 0;  /* Logical delete */
            found = F_OK;
        }

        fwrite(&temp, sizeof(Student_t), 1, temp_fp);
    }

    fclose(db_fp);
    fclose(temp_fp);

    if (found == F_OK)
    {
        remove("Students_Information.db");
        rename("Temp.db", "Students_Information.db");
    }
    else
    {
        remove("Temp.db");
    }

    return found;
}

/**
 * @brief  Displays all active students in the database.
 *
 * @details
 * - Iterates through the database file.
 * - Prints all valid student records.
 *
 * @return F_OK if records are displayed successfully.
 */
F_Return_t Show_All_Students(void) {
    FILE* db_fp = fopen("Students_Information.db", "rb");
    if (!db_fp) {
        return F_FILE_OPEN_ERROR;
    }
    else {
        /*Nothing*/
    }

    Student_t temp;
    F_Return_t found = F_FILE_IS_EMPTY;

    while (fread(&temp, sizeof(Student_t), 1, db_fp) == 1)
    {
        if (temp.is_active)
        {
            Print_Student(&temp);
            found = F_OK;  /* At least one student displayed */
        }
    }

    fclose(db_fp);
    return found;

}

/**
 * @brief  Deletes all student records from the database.
 *
 * @details
 * - Performs a full reset of the student database.
 * - Opens the database file in write-binary mode which clears all existing records.
 * - Provides feedback to the user upon successful deletion.
 *
 * @return F_OK if database cleared successfully, otherwise an error code.
 */
F_Return_t Delete_All_Students(void)
{
    FILE* db_fp = fopen("Students_Information.db", "wb");  // Open in write mode to erase all content
    if (!db_fp)
        return F_FILE_OPEN_ERROR;

    fclose(db_fp);  // Close the file after clearing

    printf("All students have been deleted successfully.\n");
    return F_OK;
}

// ----------------- helper function to make backup for data------------------------

/**
 * @brief  Creates a backup of the current student database.
 *
 * @details
 * - Copies "Students_Information.db" to "Backup_Students_Information.db".
 *
 * @return F_OK if backup succeeds, otherwise error code.
 */
static F_Return_t Backup_Student_DB(void)
{
    FILE* src = fopen("Students_Information.db", "rb");
    if (!src) return F_FILE_OPEN_ERROR;

    FILE* dest = fopen("Backup_Students_Information.db", "wb");
    if (!dest)
    {
        fclose(src);
        return F_FILE_OPEN_ERROR;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0)
    {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    printf("Database backup created successfully.\n");
    return F_OK;
}


/**
 * @brief  Deletes all student records from the database safely.
 *
 * @details
 * - Asks for user confirmation before deletion.
 * - Creates a backup before clearing the database.
 * - Opens the database in write-binary mode to erase all content.
 *
 * @return F_OK if database cleared successfully, otherwise an error code.
 */
F_Return_t Delete_All_Students_Safe(void)
{
    char confirm;
    printf("Are you sure you want to delete all students? (y/n): ");
    scanf(" %c", &confirm);
    getchar(); // consume newline

    if (confirm != 'y' && confirm != 'Y')
        return F_NOT_OK;

    // Backup before deletion
    if (Backup_Student_DB() != F_OK)
    {
        printf("Backup failed! Aborting deletion.\n");
        return F_NOT_OK;
    }

    FILE* db_fp = fopen("Students_Information.db", "wb");  // Clear all content
    if (!db_fp) return F_FILE_OPEN_ERROR;

    fclose(db_fp);
    printf("All students have been deleted successfully.\n");
    return F_OK;
}



/**
 * @brief  Restores the student database from backup.
 *
 * @details
 * - Copies "Backup_Students_Information.db" back to "Students_Information.db".
 *
 * @return F_OK if restore succeeds, otherwise error code.
 */
F_Return_t Restore_Student_DB(void)
{
    FILE* src = fopen("Backup_Students_Information.db", "rb");
    if (!src)
    {
        printf("Backup file not found!\n");
        return F_FILE_OPEN_ERROR;
    }

    FILE* dest = fopen("Students_Information.db", "wb");
    if (!dest)
    {
        fclose(src);
        return F_FILE_OPEN_ERROR;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0)
    {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    printf("Database restored from backup successfully.\n");
    return F_OK;
}