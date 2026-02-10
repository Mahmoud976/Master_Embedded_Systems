
#include"App.h"
/**
 * @brief  Runs the main application loop of the Student Management System.
 *
 * @details
 * - Displays a menu to the user.
 * - Executes selected operations.
 * - Loops until the user chooses to exit.
 */
void App_System() {
    int choice;
    uint32_t id;
    char fname[50];
    Course_t course;
    Student_t student;

    while (1)
    {
        printf("\n============================== STUDENT MANAGEMENT SYSTEM ==========================\n");
        printf("==  1. Add Student Manually                                                      ==\n");
        printf("==  2. Add Students From File                                                    ==\n");
        printf("==  3. Find Student By ID                                                        ==\n");
        printf("==  4. Find Student By First Name                                                ==\n");
        printf("==  5. Get Students By Course                                                    ==\n");
        printf("==  6. Update Student                                                            ==\n");
        printf("==  7. Delete Single Student                                                     ==\n");
        printf("==  8. Show All Students                                                         ==\n");
        printf("==  9. Delete All Students                                                       ==\n");
        printf("==  10. Restore Database from Backup                                             ==\n");
        printf("==  11. Exit                                                                     ==\n");
        printf("===================================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline after scanf

        switch (choice)
        {
        case 1:
            printf("Enter student details:\n");
            printf("ID: "); scanf("%u", &student.id);
            getchar();
            printf("First Name: "); fgets(student.first_name, sizeof(student.first_name), stdin);
            student.first_name[strcspn(student.first_name, "\n")] = 0;
            printf("Last Name: "); fgets(student.last_name, sizeof(student.last_name), stdin);
            student.last_name[strcspn(student.last_name, "\n")] = 0;
            printf("GPA: "); scanf("%f", &student.GPA);
            printf("Number of courses: "); scanf("%hhu", &student.course_count);
            for (int i = 0; i < student.course_count; i++)
            {
                printf("Course %d: ", i + 1);
                scanf("%hhu", &student.courses[i]);
            }
            student.is_active = 1;
            if (Add_Student_Manually(&student) == F_OK)
                printf("Student added successfully.\n");
            else
                printf("Error adding student.\n");
            getchar(); // consume newline
            break;

        case 2:
        {
            char filename[100];
            printf("Enter import filename: ");
            scanf("%s", filename);
            getchar();
            if (Add_Student_From_File(filename) == F_OK)
                printf("Students imported successfully.\n");
            else
                printf("Error importing students.\n");
        }
        break;

        case 3:
            printf("Enter Student ID: ");
            scanf("%u", &id);
            getchar();
            if (Find_Student_By_ID(id, &student) == F_OK)
                Print_Student(&student);
            else
                printf("Student not found.\n");
            break;

        case 4:
            printf("Enter First Name: ");
            scanf("%s", fname);
            getchar();
            if (Find_Student_By_First_Name(fname) != F_OK)
                printf("No students found with that first name.\n");
            break;

        case 5:
            printf("Enter Course ID: ");
            scanf("%hhu", &course);
            getchar();
            if (Get_Students_By_Course(course) != F_OK)
                printf("No students found in this course.\n");
            break;

        case 6:
            printf("Enter Student ID to update: ");
            scanf("%u", &id);
            getchar();
            if (Update_Student(id) == F_OK)
                printf("Student updated successfully.\n");
            else
                printf("Student not found.\n");
            break;

        case 7:
            printf("Enter Student ID to delete: ");
            scanf("%u", &id);
            getchar();
            if (Delete_Student(id) == F_OK)
                printf("Student deleted successfully.\n");
            else
                printf("Student not found.\n");
            break;

        case 8:
            if (Show_All_Students() != F_OK)
                printf("No active students to display.\n");
            break;

        case 9: // Delete All Students
            if (Delete_All_Students_Safe() == F_OK)
                printf("All students deleted successfully.\n");
            else
                printf("Database not deleted.\n");
            break;

        case 10: // Restore from Backup
            if (Restore_Student_DB() == F_OK)
                printf("Database restored from backup successfully.\n");
            else
                printf("Failed to restore database.\n");
            break;

        case 11:
            printf("Exiting program.\n");
            return;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}
