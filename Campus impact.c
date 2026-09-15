#include <stdio.h>
#include <string.h>

#define MAX_CONTRIBUTORS 100
#define POINTS_PER_HOUR 5
#define CERTIFICATE_POINTS 300

struct Contributor
{
    int id;
    char name[50];
    char department[30];
    char phone[20];
    char email[50];

    float hoursWorked;
    int points;

    char checkIn[10];
    char checkOut[10];

    char certificateStatus[20];
};

struct Contributor contributors[MAX_CONTRIBUTORS];

int contributorCount = 0;
int login();
void clearInputBuffer();
int findContributorByID(int id);
int contains(char text[], char search[]);
void inputContributorInfo(int index);
void displayContributor(int index);
void viewContributors();
void addContributor();
void searchContributor();
void editContributor();
void deleteContributor();
void recordContributionHours();
void updatePointsAndCertificate(int index);
void viewLeaderboard();
void certificateMenu();
void loadContributors();
void saveContributors();
int validTime(char time[]);
float calculateHours(char checkIn[], char checkOut[]);




int main()
{
    int choice;

    loadContributors();

    if (login() == 0)
    {
        printf("\nAccess denied.\n");
        return 0;
    }

    do
    {
        printf("\n========================================\n");
        printf(" CAMPUS IMPACT & RECOGNITION SYSTEM\n");
        printf("========================================\n");

        printf("1. View Contributors\n");
        printf("2. Add Contributor\n");
        printf("3. Search Contributor\n");
        printf("4. Edit Contributor\n");
        printf("5. Delete Contributor\n");
        printf("6. Record Contribution Hours\n");
        printf("7. View Impact Leaderboard\n");
        printf("8. Certificate\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        clearInputBuffer();

        switch (choice)
        {
            case 1:
                viewContributors();
                break;

            case 2:
                addContributor();
                break;

            case 3:
                searchContributor();
                break;

            case 4:
                editContributor();
                break;

            case 5:
                deleteContributor();
                break;

            case 6:
                recordContributionHours();
                break;

            case 7:
                viewLeaderboard();
                break;

            case 8:
                certificateMenu();
                break;

            case 0:
                printf("\nThank you for using CIRS.\n");
                break;

            default:
                printf("\nInvalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}



int login()
{
    char username[30];
    char password[30];

    printf("\n========== LOGIN ==========\n");

    printf("Username: ");
    scanf("%29s", username);

    printf("Password: ");
    scanf("%29s", password);

    if (strcmp(username, "admin") == 0 &&
        strcmp(password, "admin123") == 0)
    {
        printf("\nLogin successful!\n");
        return 1;
    }

    printf("\nIncorrect username or password.\n");

    return 0;
}



void clearInputBuffer()
{
    fflush(stdin);
}




int findContributorByID(int id)
{
    int i;

    for (i = 0; i < contributorCount; i++)
    {
        if (contributors[i].id == id)
        {
            return i;
        }
    }

    return -1;
}




int contains(char text[], char search[])
{
    int i;
    int j;

    for (i = 0; text[i] != '\0'; i++)
    {
        j = 0;

        while (search[j] != '\0' &&
               text[i + j] == search[j])
        {
            j++;
        }

        if (search[j] == '\0')
        {
            return 1;
        }
    }

    return 0;
}



void inputContributorInfo(int index)
{
    printf("Enter Name: ");
    scanf(" %49[^\n]", contributors[index].name);

    clearInputBuffer();

    printf("Enter Department: ");
    scanf(" %29[^\n]", contributors[index].department);

    clearInputBuffer();

    printf("Enter Phone: ");
    scanf("%19s", contributors[index].phone);

    printf("Enter Email: ");
    scanf("%49s", contributors[index].email);

    clearInputBuffer();
}




void displayContributor(int index)
{
    printf("\n----------------------------------------\n");

    printf("ID: %d\n", contributors[index].id);
    printf("Name: %s\n", contributors[index].name);
    printf("Department: %s\n", contributors[index].department);
    printf("Phone: %s\n", contributors[index].phone);
    printf("Email: %s\n", contributors[index].email);

    printf("Hours Worked: %.2f\n",
           contributors[index].hoursWorked);

    printf("Impact Points: %d\n",
           contributors[index].points);

    printf("Last Check-in: %s\n",
           contributors[index].checkIn);

    printf("Last Check-out: %s\n",
           contributors[index].checkOut);

    printf("Certificate Status: %s\n",
           contributors[index].certificateStatus);

    printf("----------------------------------------\n");
}




void viewContributors()
{
    int i;

    if (contributorCount == 0)
    {
        printf("\nNo contributors found.\n");
        return;
    }

    printf("\n========== ALL CONTRIBUTORS ==========\n");

    for (i = 0; i < contributorCount; i++)
    {
        displayContributor(i);
    }
}




void addContributor()
{
    int id;

    if (contributorCount >= MAX_CONTRIBUTORS)
    {
        printf("\nContributor storage is full.\n");
        return;
    }

    printf("\n========== ADD CONTRIBUTOR ==========\n");

    printf("Enter Contributor ID: ");
    scanf("%d", &id);

    clearInputBuffer();

    if (findContributorByID(id) != -1)
    {
        printf("\nThis ID already exists.\n");
        return;
    }

    contributors[contributorCount].id = id;

    inputContributorInfo(contributorCount);

    contributors[contributorCount].hoursWorked = 0;
    contributors[contributorCount].points = 0;

    strcpy(contributors[contributorCount].checkIn, "N/A");
    strcpy(contributors[contributorCount].checkOut, "N/A");

    strcpy(contributors[contributorCount].certificateStatus,
           "Not Eligible");

    contributorCount++;

    saveContributors();

    printf("\nContributor added successfully.\n");
}


void searchContributor()
{
    char searchKey[50];

    int i;
    int found = 0;

    printf("\n========== SEARCH CONTRIBUTOR ==========\n");

    printf("Enter contributor name: ");
    scanf(" %49[^\n]", searchKey);

    clearInputBuffer();

    for (i = 0; i < contributorCount; i++)
    {
        if (contains(contributors[i].name, searchKey))
        {
            displayContributor(i);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("\nNo matching contributor found.\n");
    }
}



void editContributor()
{
    int id;
    int index;

    printf("\n========== EDIT CONTRIBUTOR ==========\n");

    printf("Enter Contributor ID: ");
    scanf("%d", &id);

    clearInputBuffer();

    index = findContributorByID(id);

    if (index == -1)
    {
        printf("\nContributor not found.\n");
        return;
    }

    printf("\nCurrent Information:\n");

    displayContributor(index);

    printf("\nEnter New Information:\n");

    inputContributorInfo(index);

    saveContributors();

    printf("\nContributor updated successfully.\n");
}




void deleteContributor()
{
    int id;
    int index;
    int i;

    printf("\n========== DELETE CONTRIBUTOR ==========\n");

    printf("Enter Contributor ID: ");
    scanf("%d", &id);

    clearInputBuffer();

    index = findContributorByID(id);

    if (index == -1)
    {
        printf("\nContributor not found.\n");
        return;
    }

    printf("\nContributor Found:\n");

    displayContributor(index);

    for (i = index; i < contributorCount - 1; i++)
    {
        contributors[i] = contributors[i + 1];
    }

    contributorCount--;

    saveContributors();

    printf("\nContributor deleted successfully.\n");
}


/* VALIDATE TIME */

int validTime(char time[])
{
    int hour;
    int minute;

    if (strlen(time) != 5)
    {
        return 0;
    }

    if (time[2] != ':')
    {
        return 0;
    }

    if (time[0] < '0' || time[0] > '9' ||
        time[1] < '0' || time[1] > '9' ||
        time[3] < '0' || time[3] > '9' ||
        time[4] < '0' || time[4] > '9')
    {
        return 0;
    }

    hour = (time[0] - '0') * 10 +
           (time[1] - '0');

    minute = (time[3] - '0') * 10 +
             (time[4] - '0');

    if (hour > 23 || minute > 59)
    {
        return 0;
    }

    return 1;
}



float calculateHours(char checkIn[], char checkOut[])
{
    int inHour;
    int inMinute;

    int outHour;
    int outMinute;

    int inTotalMinutes;
    int outTotalMinutes;

    inHour = (checkIn[0] - '0') * 10 +
             (checkIn[1] - '0');

    inMinute = (checkIn[3] - '0') * 10 +
               (checkIn[4] - '0');

    outHour = (checkOut[0] - '0') * 10 +
              (checkOut[1] - '0');

    outMinute = (checkOut[3] - '0') * 10 +
                (checkOut[4] - '0');

    inTotalMinutes = inHour * 60 + inMinute;
    outTotalMinutes = outHour * 60 + outMinute;

    return (outTotalMinutes - inTotalMinutes) / 60.0;
}



void recordContributionHours()
{
    int id;
    int index;

    float sessionHours;

    char checkIn[10];
    char checkOut[10];

    struct Contributor *c;

    printf("\n====== RECORD CONTRIBUTION HOURS ======\n");

    printf("Enter Contributor ID: ");
    scanf("%d", &id);

    clearInputBuffer();

    index = findContributorByID(id);

    if (index == -1)
    {
        printf("\nContributor not found.\n");
        return;
    }

    c = &contributors[index];

    printf("Enter Check-in Time (HH:MM): ");
    scanf("%9s", checkIn);

    clearInputBuffer();

    if (validTime(checkIn) == 0)
    {
        printf("\nInvalid check-in time.\n");
        return;
    }

    printf("Enter Check-out Time (HH:MM): ");
    scanf("%9s", checkOut);

    clearInputBuffer();

    if (validTime(checkOut) == 0)
    {
        printf("\nInvalid check-out time.\n");
        return;
    }

    sessionHours = calculateHours(checkIn, checkOut);

    if (sessionHours <= 0)
    {
        printf("\nInvalid time range.\n");
        printf("Check-out must be after check-in.\n");
        return;
    }

    strcpy(c->checkIn, checkIn);
    strcpy(c->checkOut, checkOut);

    c->hoursWorked = c->hoursWorked + sessionHours;

    updatePointsAndCertificate(index);

    saveContributors();

    printf("\nContribution recorded successfully!\n");

    printf("Hours this session: %.2f\n",
           sessionHours);

    printf("Total hours worked: %.2f\n",
           c->hoursWorked);

    printf("Impact points: %d\n",
           c->points);
}



void updatePointsAndCertificate(int index)
{
    contributors[index].points =
        (int)(contributors[index].hoursWorked *
              POINTS_PER_HOUR);

    if (contributors[index].points >= CERTIFICATE_POINTS)
    {
        if (strcmp(contributors[index].certificateStatus,
                   "Collected") != 0)
        {
            strcpy(contributors[index].certificateStatus,
                   "Eligible");
        }
    }
    else
    {
        if (strcmp(contributors[index].certificateStatus,
                   "Collected") != 0)
        {
            strcpy(contributors[index].certificateStatus,
                   "Not Eligible");
        }
    }
}




void viewLeaderboard()
{
    struct Contributor sorted[MAX_CONTRIBUTORS];
    struct Contributor temp;

    int i;
    int j;

    if (contributorCount == 0)
    {
        printf("\nNo contributors available.\n");
        return;
    }

    for (i = 0; i < contributorCount; i++)
    {
        sorted[i] = contributors[i];
    }

    for (i = 0; i < contributorCount - 1; i++)
    {
        for (j = 0;
             j < contributorCount - i - 1;
             j++)
        {
            if (sorted[j].points < sorted[j + 1].points)
            {
                temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("\n==============================================\n");
    printf("           CAMPUS IMPACT LEADERBOARD\n");
    printf("==============================================\n");

    printf("%-6s %-20s %-10s %-10s\n",
           "Rank",
           "Name",
           "Hours",
           "Points");

    printf("----------------------------------------------\n");

    for (i = 0; i < contributorCount; i++)
    {
        printf("%-6d %-20s %-10.2f %-10d\n",
               i + 1,
               sorted[i].name,
               sorted[i].hoursWorked,
               sorted[i].points);
    }

    printf("==============================================\n");
}



void certificateMenu()
{
    int id;
    int index;
    int choice;

    struct Contributor *c;

    printf("\n========== CERTIFICATE ==========\n");

    printf("Enter Contributor ID: ");
    scanf("%d", &id);

    clearInputBuffer();

    index = findContributorByID(id);

    if (index == -1)
    {
        printf("\nContributor not found.\n");
        return;
    }

    c = &contributors[index];

    printf("\nContributor: %s\n", c->name);

    printf("Hours Worked: %.2f\n",
           c->hoursWorked);

    printf("Impact Points: %d\n",
           c->points);

    printf("Certificate Status: %s\n",
           c->certificateStatus);

    if (strcmp(c->certificateStatus, "Collected") == 0)
    {
        printf("\nCertificate has already been collected.\n");
        return;
    }

    if (c->points < CERTIFICATE_POINTS)
    {
        printf("\nCertificate not available yet.\n");

        printf("Points Required: %d\n",
               CERTIFICATE_POINTS);

        printf("Current Points: %d\n",
               c->points);

        printf("Points Needed: %d\n",
               CERTIFICATE_POINTS - c->points);

        return;
    }

    printf("\nCongratulations!\n");
    printf("You are eligible to receive a certificate.\n");

    printf("\n1. Collect Certificate\n");
    printf("0. Go Back\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    clearInputBuffer();

    if (choice == 1)
    {
        strcpy(c->certificateStatus, "Collected");

        saveContributors();

        printf("\nCertificate collected successfully!\n");
    }
    else if (choice == 0)
    {
        printf("\nReturning to main menu...\n");
    }
    else
    {
        printf("\nInvalid choice.\n");
    }
}



void loadContributors()
{
    FILE *fp;
    int result;

    fp = fopen("contributors.txt", "r");

    if (fp == NULL)
    {
        return;
    }

    while (contributorCount < MAX_CONTRIBUTORS)
    {
        result = fscanf(fp,
                        "%d|%49[^|]|%29[^|]|%19[^|]|%49[^|]|%f|%d|%9[^|]|%9[^|]|%19[^\n]",
                        &contributors[contributorCount].id,
                        contributors[contributorCount].name,
                        contributors[contributorCount].department,
                        contributors[contributorCount].phone,
                        contributors[contributorCount].email,
                        &contributors[contributorCount].hoursWorked,
                        &contributors[contributorCount].points,
                        contributors[contributorCount].checkIn,
                        contributors[contributorCount].checkOut,
                        contributors[contributorCount].certificateStatus);

        if (result == EOF)
        {
            break;
        }

        if (result == 10)
        {
            contributorCount++;
        }
        else
        {
            break;
        }
    }

    fclose(fp);
}



void saveContributors()
{
    FILE *fp;
    int i;

    fp = fopen("contributors.txt", "w");

    if (fp == NULL)
    {
        printf("\nUnable to open file.\n");
        return;
    }

    for (i = 0; i < contributorCount; i++)
    {
        fprintf(fp,
                "%d|%s|%s|%s|%s|%.2f|%d|%s|%s|%s\n",
                contributors[i].id,
                contributors[i].name,
                contributors[i].department,
                contributors[i].phone,
                contributors[i].email,
                contributors[i].hoursWorked,
                contributors[i].points,
                contributors[i].checkIn,
                contributors[i].checkOut,
                contributors[i].certificateStatus);
    }

    fclose(fp);
}

