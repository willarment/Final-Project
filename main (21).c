#include <stdio.h>
#include <time.h>
#include <string.h>

// Structure to store employee information
struct Employee {
    char name[50];
    float hourly_pay;
};

// Structure to store daily work hours
struct DailyHours {
    struct tm clock_in;
    struct tm clock_out;
};

// Function to get employee information
struct Employee get_employee_info() {
    struct Employee emp;
    printf("Enter employee first name: ");
    scanf("%s", emp.name);
    printf("Enter employee last name: ");
    scanf("%s", emp.name + strlen(emp.name) + 1); // Append last name after a space
    printf("Enter hourly pay: $");
    scanf("%f", &emp.hourly_pay);
    return emp;
}

// Function to get daily work hours
struct DailyHours get_daily_hours() {
    struct DailyHours hours;
    char time_str[10]; // Input buffer for clock in/out times
    int year, month, day, hour, minute;

    printf("Enter clock-in time (HH:MM) in Millitary Time Format: "); //no need for A.M. or P.M. reference
    scanf("%s", time_str);
    sscanf(time_str, "%d:%d", &hour, &minute);
    hours.clock_in.tm_hour = hour;
    hours.clock_in.tm_min = minute;

    printf("Enter clock-out time (HH:MM) in Millitary Time Format: ");
    scanf("%s", time_str);
    sscanf(time_str, "%d:%d", &hour, &minute);
    hours.clock_out.tm_hour = hour;
    hours.clock_out.tm_min = minute;

    // Assuming the current date (adjust if needed)
    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    hours.clock_in.tm_year = current_time->tm_year;
    hours.clock_in.tm_mon = current_time->tm_mon;
    hours.clock_in.tm_mday = current_time->tm_mday;
    hours.clock_out.tm_year = current_time->tm_year;
    hours.clock_out.tm_mon = current_time->tm_mon;
    hours.clock_out.tm_mday = current_time->tm_mday;

    return hours;
}
//Tax rates for U.S. jobs are on average 15.3%
// Function to calculate weekly pay
float calculate_weekly_pay(struct Employee emp, float total_hours) {
    float gross_pay = emp.hourly_pay * total_hours;
    float social_security_tax_rate = 0.124; // Example tax rate (12.4%)
    float disability_insurance_tax_rate = 0.029; // Example tax rate (2.9%)
    float tax_rate = social_security_tax_rate + disability_insurance_tax_rate; // Example tax rate (15.3%)
    float tax_amount = gross_pay * tax_rate;
    return gross_pay - tax_amount;
}

int main() {
    struct Employee employee = get_employee_info();
    float total_hours = 0;

    // Loop through days of the week
    for (int day = 0; day < 7; day++) {
        printf("\nDay %d:\n", day + 1);
        struct DailyHours hours = get_daily_hours();

        // Calculate daily hours worked
        int total_minutes = (hours.clock_out.tm_hour * 60 + hours.clock_out.tm_min) - 
                            (hours.clock_in.tm_hour * 60 + hours.clock_in.tm_min);
        float daily_hours = (float)total_minutes / 60; 

        total_hours += daily_hours;
    }

    // Calculate and print net pay
    float net_pay = calculate_weekly_pay(employee, total_hours);
    printf("\nEmployee: %s\n", employee.name);
    printf("Weekly Pay: $%.2f\n", net_pay);

    return 0;
}