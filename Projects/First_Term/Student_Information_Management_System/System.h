#ifndef STUDENT_SYSTEM_H
#define STUDENT_SYSTEM_H


/* ============================================================
 *  Student Management System
 *
 *  Description:
 *  This module provides a complete student management system
 *  using a file-based database. All student records are stored
 *  persistently in an external binary file acting as the main
 *  database. The APIs support CRUD operations such as add,
 *  update, delete, search, and display.
 * ============================================================ */

#include"String.h"
 /* ============================================================
  *                    Configuration Macros
  * ============================================================ */
#define MAX_NAME_LENGTH    50
#define MAX_COURSES        10
#define MAX_COURSE_ID      10

  /* ============================================================
   *                    Courses Enumeration
   *
   *  Description:
   *  Represents all supported courses in the system.
   * ============================================================ */
typedef enum
{
    COURSE_MATH = 0,
    COURSE_PHYSICS,
    COURSE_OS,
    COURSE_CA,
    COURSE_DB,
    COURSE_C_PROGRAMMING,
    COURSE_EMBEDDED_C,
    COURSE_DS,
    COURSE_IOT,
    COURSE_AI
} Course_t;

/* ============================================================
 *                Function Return Status Codes
 *
 *  Description:
 *  Used by all system APIs to indicate operation result.
 * ============================================================ */
typedef enum
{
    F_OK = 0,                 /* Operation completed successfully */
    F_NOT_OK,                 /* Generic failure */
    F_FILE_OPEN_ERROR,        /* Failed to open database file */
    F_FILE_READ_ERROR,        /* File read error */
    F_FILE_WRITE_ERROR,       /* File write error */
    F_ID_ALREADY_EXISTS,      /* Student ID already exists */
    F_ID_NOT_FOUND,           /* Student ID not found */
    F_FNAME_NOT_FOUND,        /* First name not found */
    F_COURSE_NOT_FOUND,       /* Course not found */
    F_FILE_IS_EMPTY,          /* DataBase  Empty */  
} F_Return_t;

/* ============================================================
 *                    Student Data Structure
 *
 *  Description:
 *  Represents a single student record stored in the database.
 * ============================================================ */
typedef struct
{
    uint32_t id;                                /* Unique student ID */
    char first_name[MAX_NAME_LENGTH];           /* Student first name */
    char last_name[MAX_NAME_LENGTH];            /* Student last name */
    float GPA;                                  /* Student GPA */
    uint8_t courses[MAX_COURSES];               /* Registered courses */
    uint8_t course_count;                       /* Number of courses */
    bool is_active;                             /* Logical delete flag */
} Student_t;

/* ============================================================
 *                    System API Functions
 * ============================================================ */

 /**
  * @brief  Initializes the student management system.
  *
  * @details
  * - Creates the database file if it does not exist.
  * - Prepares the system for file-based operations.
  *
  * @return F_OK if initialization succeeds, otherwise error code.
  */
F_Return_t System_Init(void);

/**
 * @brief  Imports student records from an external file.
 *
 * @details
 * - Reads student data from an external file.
 * - Validates records before inserting them into the main database.
 * - Prevents duplicate student IDs.
 *
 * @param  import_file Path to the external input file.
 * @return F_OK if import succeeds, otherwise error code.
 */
F_Return_t Add_Student_From_File(const char* import_file);

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
F_Return_t Add_Student_Manually(const Student_t* student);
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
F_Return_t Find_Student_By_ID(uint32_t id, Student_t* student);

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
F_Return_t Find_Student_By_First_Name(const char* fname);

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
F_Return_t Get_Students_By_Course(Course_t course);

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
F_Return_t Update_Student(uint32_t id);

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
F_Return_t Delete_Student(uint32_t id);

/**
 * @brief  Displays all active students in the database.
 *
 * @details
 * - Iterates through the database file.
 * - Prints all valid student records.
 *
 * @return F_OK if records are displayed successfully.
 */
F_Return_t Show_All_Students(void);


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
F_Return_t Delete_All_Students_Safe(void);


/**
 * @brief  Restores the student database from backup.
 *
 * @details
 * - Copies "Backup_Students_Information.db" back to "Students_Information.db".
 *
 * @return F_OK if restore succeeds, otherwise error code.
 */
F_Return_t Restore_Student_DB(void);


#endif /* STUDENT_SYSTEM_H */
