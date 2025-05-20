#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Define patient structure
struct Patient {
    int mrNumber;
    char name[50];
    int age;
};

// Define service structure
struct Service {
    char name[50];
    int price;
};

// Hardcoded patient database
struct Patient patientDB[] = {
    {2001, "Ahmed\n", 30},
    {2002, "Sara\n", 25},
    {2003, "Sahul\n", 78},
    {2004, "Fatima\n", 40},
    {2005, "Arsh\n", 20}
};

// Cardiology services
struct Service cardiologyServices[] = {
    {"Echo Cardiogram", 5000},
    {"Angiography", 15000},
    {"Stress Test", 4000},
    {"Holter Monitoring", 3500},
    {"ECG", 1000},
    {"Pacemaker Implant", 18000}
};

// Neurology services
struct Service neurologyServices[] = {
    {"EEG", 2500},
    {"Brain MRI", 12000},
    {"Nerve Conduction Study", 4000},
    {"Spinal Tap", 7000},
    {"Neuro Consultation", 2000}
};

// Orthopedics services
struct Service orthoServices[] = {
    {"X-Ray", 1000},
    {"Joint Replacement", 30000},
    {"Fracture Fixation", 8000},
    {"Arthroscopy", 15000},
    {"Physiotherapy", 2000}
};

// General Medicine services
struct Service generalServices[] = {
    {"Consultation", 1000},
    {"Blood Test", 500},
    {"Urine Test", 300},
    {"Vaccination", 700},
    {"Health Check-up", 2000}
};

// Organization discount percentages
struct OrgDiscount {
    char name[20];
    float discountPercent;
} orgDiscounts[] = {
    {"pia", 20.0},
    {"army", 25.0},
    {"police", 15.0},
    {"nadra", 10.0}
};

#define ORG_DISCOUNT_COUNT (sizeof(orgDiscounts)/sizeof(orgDiscounts[0]))

// Function to print hospital header
void printHeader(char hospitalName[], int mrNumber) {
    printf("\n====================================\n");
    printf("       %s\n", hospitalName);
    printf("====================================\n");
    printf("MR Number  : %d\n", mrNumber);
    printf("====================================\n\n");
}

// Function to print patient information
void printPatientInfo(char name[], int age, char department[]) {
    printf("------------------------------------\n");
    printf("Patient Name : %s", name);
    printf("Age          : %d\n", age);
    printf("Department   : %s", department);
    printf("------------------------------------\n");
}

// Function to print charges and total with discount and GST
void printCharges(int room, int medicines, int tests, int surgery, int serviceCharges, float discountPercent) {
    float subtotal = room + medicines + tests + surgery + serviceCharges;
    float discountAmount = subtotal * (discountPercent / 100.0f);
    float discountedSubtotal = subtotal - discountAmount;
    float gst = discountedSubtotal * 0.05f;  // 5% GST
    float total = discountedSubtotal + gst;

    printf("Charges Breakdown:\n");
    printf("------------------------------------\n");
    printf("Room        : %d\n", room);
    printf("Medicines   : %d\n", medicines);
    printf("Tests       : %d\n", tests);
    printf("Surgery     : %d\n", surgery);
    printf("Department Services : %d\n", serviceCharges);
    printf("------------------------------------\n");
    printf("Subtotal    : %.2f\n", subtotal);
    if (discountPercent > 0) {
        printf("Discount (%.0f%%) : -%.2f\n", discountPercent, discountAmount);
        printf("------------------------------------\n");
        printf("Subtotal after discount : %.2f\n", discountedSubtotal);
    }
    printf("GST (5%%)   : %.2f\n", gst);
    printf("Total Bill  : %.2f\n", total);
    printf("\n====================================\n");
    printf("   Thank You! Get Well Soon!\n");
    printf("====================================\n");
}

// Function to print bar for bar chart
void printBar(char label[], int value) {
    printf("%s: ", label);
    for (int i = 0; i < value; i++) {
        printf("*");
    }
    printf(" (%d)\n", value * 1000);
}

// Function to print entire bar chart for charges
void printBarChart(int room, int medicines, int tests, int surgery, int serviceCharges) {
    printf("\n\nHOSPITAL CHARGES BAR CHART\n");
    printf("------------------------------------\n");
    printBar("Room", room / 1000);
    printBar("Medicines", medicines / 1000);
    printBar("Tests", tests / 1000);
    printBar("Surgery", surgery / 1000);
    printBar("Dept Services", serviceCharges / 1000);
    printf("------------------------------------\n");
}

// Function to select department
int selectDepartment(char departmentName[]) {
    int choice;
    printf("Select Department:\n");
    printf("1. Cardiology\n");
    printf("2. Neurology\n");
    printf("3. Orthopedics\n");
    printf("4. General Medicine\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline

    switch (choice) {
        case 1: strcpy(departmentName, "Cardiology\n"); break;
        case 2: strcpy(departmentName, "Neurology\n"); break;
        case 3: strcpy(departmentName, "Orthopedics\n"); break;
        case 4: strcpy(departmentName, "General Medicine\n"); break;
        default: strcpy(departmentName, "Unknown\n"); break;
    }
    return choice;
}

// Function to select services for a department
int selectDepartmentServices(int deptChoice) {
    int total = 0, sChoice;
    struct Service* services;
    int size;

    switch (deptChoice) {
        case 1: services = cardiologyServices;
            size = sizeof(cardiologyServices)/sizeof(cardiologyServices[0]); break;
        case 2: services = neurologyServices;
            size = sizeof(neurologyServices)/sizeof(neurologyServices[0]); break;
        case 3: services = orthoServices;
            size = sizeof(orthoServices)/sizeof(orthoServices[0]); break;
        case 4: services = generalServices;
            size = sizeof(generalServices)/sizeof(generalServices[0]); break;
        default: return 0;
    }

    printf("Available Services:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - %d\n", i + 1, services[i].name, services[i].price);
    }
    printf("Enter service numbers one by one. Enter -1 to finish:\n");
    do {
        scanf("%d", &sChoice);
        if (sChoice > 0 && sChoice <= size) {
            total += services[sChoice - 1].price;
        }
    } while (sChoice != -1);
    getchar(); // consume newline after input

    return total;
}

// Function to get discount percent based on organization affiliation
float getOrgDiscount(void) {
    char response[10];
    char orgName[20];
    float discount = 0.0f;

    printf("Are you affiliated with any organization? (yes/no): ");
    while ((getchar()) != '\n'); // flush any leftover input before fgets
    fgets(response, sizeof(response), stdin);

    // lowercase response for safe check
    for (int i = 0; response[i]; i++) {
        response[i] = tolower(response[i]);
    }

    if (strncmp(response, "yes", 3) == 0) {
        printf("Enter organization name (pia, army, police, nadra): ");
        fgets(orgName, sizeof(orgName), stdin);

        // convert orgName to lowercase & trim newline
        for (int i = 0; orgName[i]; i++) {
            if (orgName[i] == '\n') {
                orgName[i] = '\0';
                break;
            }
            orgName[i] = tolower(orgName[i]);
        }

        for (int i = 0; i < ORG_DISCOUNT_COUNT; i++) {
            if (strcmp(orgName, orgDiscounts[i].name) == 0) {
                discount = orgDiscounts[i].discountPercent;
                break;
            }
        }
        if (discount == 0.0f) {
            printf("No discount available for this organization.\n");
        } else {
            printf("Discount of %.0f%% applied.\n", discount);
        }
    } else {
        discount = 0.0f;
    }
    return discount;
}

int main(void) {
    int mrInput;
    char department[30], hospitalName[50];
    int roomCharges = 0, medicinesCharges = 0, testsCharges = 0, surgeryCharges = 0;
    int serviceCharges = 0;
    int found = 0;
    char name[50];
    int age;
    float discountPercent;

    printf("Enter Hospital Name: ");
    fgets(hospitalName, sizeof(hospitalName), stdin);

    printf("Enter MR Number: ");
    scanf("%d", &mrInput);
    getchar(); // consume newline

    for (int i = 0; i < 5; i++) {
        if (mrInput == patientDB[i].mrNumber) {
            int deptChoice = selectDepartment(department);
            serviceCharges = selectDepartmentServices(deptChoice);

            printf("Enter Room Charges: ");
            scanf("%d", &roomCharges);

            printf("Enter Medicines Charges: ");
            scanf("%d", &medicinesCharges);

            printf("Enter Tests Charges: ");
            scanf("%d", &testsCharges);

            printf("Enter Surgery Charges: ");
            scanf("%d", &surgeryCharges);

            discountPercent = getOrgDiscount();

            printHeader(hospitalName, mrInput);
            printPatientInfo(patientDB[i].name, patientDB[i].age, department);
            printCharges(roomCharges, medicinesCharges, testsCharges, surgeryCharges, serviceCharges, discountPercent);
            printBarChart(roomCharges, medicinesCharges, testsCharges, surgeryCharges, serviceCharges);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nMR Number not found in system.\nPlease Enter Manually\n\n");
        printf("Enter Patient Name: ");
        fgets(name, sizeof(name), stdin);

        printf("Enter Age: ");
        scanf("%d", &age);
        getchar();

        int deptChoice = selectDepartment(department);
        serviceCharges = selectDepartmentServices(deptChoice);

        printf("Enter Room Charges: ");
        scanf("%d", &roomCharges);

        printf("Enter Medicines Charges: ");
        scanf("%d", &medicinesCharges);

        printf("Enter Tests Charges: ");
        scanf("%d", &testsCharges);

        printf("Enter Surgery Charges: ");
        scanf("%d", &surgeryCharges);

        discountPercent = getOrgDiscount();

        printHeader(hospitalName, mrInput);
        printPatientInfo(name, age, department);
        printCharges(roomCharges, medicinesCharges, testsCharges, surgeryCharges, serviceCharges, discountPercent);
        printBarChart(roomCharges, medicinesCharges, testsCharges, surgeryCharges, serviceCharges);
    }

    return 0;
}
