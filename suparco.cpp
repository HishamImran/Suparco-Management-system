#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

// ==================== GLOBAL CONSTANTS ====================
const int MAX_APPLICATIONS = 100;
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 700;

// ==================== DATA STRUCTURES ====================
struct Applicant {
    string name;
    string cnic;
    string category;
    string role;
    string status;
    string email;
    string phone;
    string education;
    string experience;
    string applicationDate;
    int age;
};

struct Feedback {
    string name;
    string email;
    string message;
    string date;
    int rating;
};

struct NewsItem {
    string title;
    string content;
    string date;
};

// ==================== GLOBAL VARIABLES ====================
Applicant applications[MAX_APPLICATIONS];
int totalApplications = 0;

Feedback feedbacks[50];
int totalFeedbacks = 0;

string adminPassword = "";
string secretPassword = "";
bool isPasswordSet = false;

HWND hwndMain;
HINSTANCE hInst;

// Color scheme
COLORREF COLOR_PRIMARY = RGB(0, 51, 102);      // Dark Blue
COLORREF COLOR_SECONDARY = RGB(0, 102, 204);  // Light Blue
COLORREF COLOR_ACCENT = RGB(255, 140, 0);     // Orange
COLORREF COLOR_BG = RGB(240, 248, 255);       // Light background
COLORREF COLOR_TEXT = RGB(0, 0, 0);           // Black text

// ==================== WINDOW IDENTIFIERS ====================
#define ID_MAIN_MENU 1000
#define ID_APPLY_MENU 1001
#define ID_ADMIN_MENU 1002
#define ID_ABOUT_MENU 1003
#define ID_NEWS_MENU 1004
#define ID_PROJECTS_MENU 1005
#define ID_FEEDBACK_MENU 1006
#define ID_CONTACT_MENU 1007
#define ID_RESEARCH_MENU 1008
#define ID_SATELLITE_MENU 1009
#define ID_COOPERATION_MENU 1010
#define ID_GIS_MENU 1011
#define ID_PASSWORD_SETUP 1012
#define ID_EXIT 1013

// Button IDs for Apply Section
#define ID_BTN_JOB 2001
#define ID_BTN_INTERNSHIP 2002
#define ID_BTN_RESEARCH 2003
#define ID_BTN_SUBMIT_APP 2004
#define ID_BTN_BACK 2005

// Button IDs for Admin Section

#define ID_BTN_ADMIN_LOGIN   7003
// (optional cancel) #define ID_BTN_ADMIN_CANCEL 700

// Unique ID for feedback submit (choose any unused high number)
#define ID_BTN_SUBMIT_FEEDBACK 7002

#define ID_BTN_VIEW_APPS 3001
#define ID_BTN_APPROVE 3002
#define ID_BTN_REJECT 3003
#define ID_BTN_STATS 3004
#define ID_BTN_EXPORT 3005

// Edit control IDs
#define ID_EDIT_NAME 4001
#define ID_EDIT_CNIC 4002
#define ID_EDIT_AGE 4003
#define ID_EDIT_EMAIL 4004
#define ID_EDIT_PHONE 4005
#define ID_EDIT_EDUCATION 4006
#define ID_EDIT_EXPERIENCE 4007
#define ID_EDIT_PASSWORD 4008
#define ID_EDIT_CNIC_SEARCH 4009
#define ID_EDIT_FEEDBACK 4010
#define ID_EDIT_FEEDBACK_NAME 4011
#define ID_EDIT_FEEDBACK_EMAIL 4012

// Combo box IDs
#define ID_COMBO_JOB_TYPE 5001
#define ID_COMBO_INTERN_TYPE 5002
#define ID_COMBO_RATING 5003

// Listbox IDs
#define ID_LIST_APPLICATIONS 6001
#define ID_LIST_NEWS 6002

// ==================== UTILITY FUNCTIONS ====================


// Safe current date-time
string getCurrentDateTime() {
    time_t now = time(nullptr);
    tm timeinfo{};
    // For MSVC: localtime_s(&timeinfo, &now);
    // For portable (and fine on MinGW): 
    tm* lt = localtime(&now);
    if (lt) timeinfo = *lt;

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return string(buffer);
}

// Safe current date only
string getCurrentDate() {
    time_t now = time(nullptr);
    tm timeinfo{};
    tm* lt = localtime(&now);
    if (lt) timeinfo = *lt;

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeinfo);
    return string(buffer);
}


// Validate password strength
bool validatePassword(const string& password, string& errorMsg) {
    if (password.length() < 6) {
        errorMsg = "Password must be at least 6 characters long!";
        return false;
    }
    
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    
    for (size_t i = 0; i < password.length(); i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') hasUpper = true;
        else if (password[i] >= 'a' && password[i] <= 'z') hasLower = true;
        else if (password[i] >= '0' && password[i] <= '9') hasDigit = true;
        else hasSpecial = true;
    }
    
    if (!hasUpper) {
        errorMsg = "Password must include at least 1 uppercase letter!";
        return false;
    }
    if (!hasLower) {
        errorMsg = "Password must include at least 1 lowercase letter!";
        return false;
    }
    if (!hasDigit) {
        errorMsg = "Password must include at least 1 number!";
        return false;
    }
    if (!hasSpecial) {
        errorMsg = "Password must include at least 1 special character!";
        return false;
    }
    
    return true;
}

// Validate CNIC format (13 digits)
bool validateCNIC(const string& cnic) {
    if (cnic.length() != 13) return false;
    for (size_t i = 0; i < cnic.length(); i++) {
        if (cnic[i] < '0' || cnic[i] > '9') return false;
    }
    return true;
}

// Validate email format
bool validateEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    return (atPos != string::npos && dotPos != string::npos && atPos > 0 && dotPos > atPos + 1);
}

// Validate phone number (11 digits)
bool validatePhone(const string& phone) {
    if (phone.length() != 11) return false;
    for (size_t i = 0; i < phone.length(); i++) {
        if (phone[i] < '0' || phone[i] > '9') return false;
    }
    return true;
}

// Convert string to integer
int stringToInt(const string& str) {
    int result = 0;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}

// Convert integer to string
string intToString(int num) {
    if (num == 0) return "0";
    string result = "";
    bool negative = false;
    if (num < 0) {
        negative = true;
        num = -num;
    }
    while (num > 0) {
        result = char('0' + (num % 10)) + result;
        num /= 10;
    }
    if (negative) result = "-" + result;
    return result;
}

// ==================== FILE OPERATIONS ====================

// Save application to file
void saveApplicationToFile(const Applicant& app) {
    ofstream file("applications.txt", ios::app);
    if (file.is_open()) {
        file << "=== APPLICATION ===" << endl;
        file << "Name: " << app.name << endl;
        file << "CNIC: " << app.cnic << endl;
        file << "Age: " << app.age << endl;
        file << "Email: " << app.email << endl;
        file << "Phone: " << app.phone << endl;
        file << "Education: " << app.education << endl;
        file << "Experience: " << app.experience << endl;
        file << "Category: " << app.category << endl;
        file << "Role: " << app.role << endl;
        file << "Status: " << app.status << endl;
        file << "Date: " << app.applicationDate << endl;
        file << "===================" << endl << endl;
        file.close();
    }
}

// Save feedback to file
void saveFeedbackToFile(const Feedback& fb) {
    ofstream file("feedback.txt", ios::app);
    if (file.is_open()) {
        file << "=== FEEDBACK ===" << endl;
        file << "Name: " << fb.name << endl;
        file << "Email: " << fb.email << endl;
        file << "Rating: " << fb.rating << "/5" << endl;
        file << "Message: " << fb.message << endl;
        file << "Date: " << fb.date << endl;
        file << "===================" << endl << endl;
        file.close();
    }
}

// Save passwords to file
void savePasswordsToFile() {
    ofstream file("passwords.dat");
    if (file.is_open()) {
        file << adminPassword << endl;
        file << secretPassword << endl;
        file.close();
    }
}

// Load passwords from file
void loadPasswordsFromFile() {
    ifstream file("passwords.dat");
    if (file.is_open()) {
        getline(file, adminPassword);
        getline(file, secretPassword);
        if (!adminPassword.empty() && !secretPassword.empty()) {
            isPasswordSet = true;
        }
        file.close();
    }
}

// Export statistics to file
void exportStatistics() {
    ofstream file("statistics_report.txt");
    if (file.is_open()) {
        file << "========================================" << endl;
        file << "   SUPARCO STATISTICS REPORT" << endl;
        file << "   Generated: " << getCurrentDateTime() << endl;
        file << "========================================" << endl << endl;
        
        file << "Total Applications: " << totalApplications << endl << endl;
        
        // Count by status
        int pending = 0, approved = 0, rejected = 0;
        for (int i = 0; i < totalApplications; i++) {
            if (applications[i].status == "Pending") pending++;
            else if (applications[i].status == "Approved") approved++;
            else if (applications[i].status == "Rejected") rejected++;
        }
        
        file << "Status Breakdown:" << endl;
        file << "  Pending: " << pending << endl;
        file << "  Approved: " << approved << endl;
        file << "  Rejected: " << rejected << endl << endl;
        
        // Count by category
        int jobs = 0, internships = 0, research = 0;
        for (int i = 0; i < totalApplications; i++) {
            if (applications[i].category.find("Job") != string::npos) jobs++;
            else if (applications[i].category.find("Internship") != string::npos) internships++;
            else if (applications[i].category.find("Research") != string::npos) research++;
        }
        
        file << "Category Breakdown:" << endl;
        file << "  Jobs: " << jobs << endl;
        file << "  Internships: " << internships << endl;
        file << "  Research: " << research << endl << endl;
        
        file << "========================================" << endl;
        file.close();
        
        MessageBox(hwndMain, "Statistics exported successfully to 'statistics_report.txt'!", 
                   "Success", MB_OK | MB_ICONINFORMATION);
    }
}

// ==================== WINDOW PROCEDURES FOR DIFFERENT SCREENS ====================

// Clear all child windows
void clearScreen(HWND hwnd) {
    HWND child = GetWindow(hwnd, GW_CHILD);
    while (child != NULL) {
        HWND next = GetWindow(child, GW_HWNDNEXT);
        DestroyWindow(child);
        child = next;
    }
    InvalidateRect(hwnd, NULL, TRUE);
}

// ==================== PASSWORD SETUP SCREEN ====================
void showPasswordSetupScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    // Title
    CreateWindow("STATIC", "SYSTEM SETUP - Set Passwords",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 30, 500, 40, hwnd, NULL, hInst, NULL);
    
    // Admin Password Section
    CreateWindow("STATIC", "Admin Password:",
                 WS_VISIBLE | WS_CHILD,
                 150, 100, 200, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD,
                 150, 130, 300, 25, hwnd, (HMENU)ID_EDIT_PASSWORD, hInst, NULL);
    
    CreateWindow("STATIC", "Requirements: Min 6 chars, uppercase, lowercase, number, special char",
                 WS_VISIBLE | WS_CHILD,
                 150, 160, 500, 25, hwnd, NULL, hInst, NULL);
    
    // Secret Password Section
    CreateWindow("STATIC", "Confidential Projects Password:",
                 WS_VISIBLE | WS_CHILD,
                 150, 210, 300, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD,
                 150, 240, 300, 25, hwnd, (HMENU)(ID_EDIT_PASSWORD + 1), hInst, NULL);
    
    CreateWindow("STATIC", "Requirements: Min 6 chars, uppercase, lowercase, number, special char",
                 WS_VISIBLE | WS_CHILD,
                 150, 270, 500, 25, hwnd, NULL, hInst, NULL);
    
    // Submit Button
    CreateWindow("BUTTON", "Set Passwords",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 300, 330, 150, 35, hwnd, (HMENU)ID_PASSWORD_SETUP, hInst, NULL);
}

// ==================== MAIN MENU SCREEN ====================
void showMainMenu(HWND hwnd) {
    clearScreen(hwnd);
    
    // Title
    CreateWindow("STATIC", "SUPARCO - Space & Upper Atmosphere Research Commission",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 50, 20, 800, 40, hwnd, NULL, hInst, NULL);
    
    CreateWindow("STATIC", "Main Menu - Select an Option",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 50, 60, 800, 30, hwnd, NULL, hInst, NULL);
    
    // Menu Buttons - Column 1
    CreateWindow("BUTTON", "Apply (Jobs/Internships/Research)",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 100, 120, 300, 40, hwnd, (HMENU)ID_APPLY_MENU, hInst, NULL);
    
    CreateWindow("BUTTON", "Admin Control Panel",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 100, 170, 300, 40, hwnd, (HMENU)ID_ADMIN_MENU, hInst, NULL);
    
    CreateWindow("BUTTON", "News & Updates",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 100, 220, 300, 40, hwnd, (HMENU)ID_NEWS_MENU, hInst, NULL);
    
    CreateWindow("BUTTON", "About SUPARCO",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 100, 270, 300, 40, hwnd, (HMENU)ID_ABOUT_MENU, hInst, NULL);
    
    CreateWindow("BUTTON", "Projects & Services",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 100, 320, 300, 40, hwnd, (HMENU)ID_PROJECTS_MENU, hInst, NULL);
    
    CreateWindow("BUTTON", "Research Programs",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 100, 370, 300, 40, hwnd, (HMENU)ID_RESEARCH_MENU, hInst, NULL);
    
    // Menu Buttons - Column 2
    CreateWindow("BUTTON", "Remote Sensing & GIS Services",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 500, 120, 300, 40, hwnd, (HMENU)ID_GIS_MENU, hInst, NULL);
    
    CreateWindow("BUTTON", "International Cooperation",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 500, 170, 300, 40, hwnd, (HMENU)ID_COOPERATION_MENU, hInst, NULL);
    
    CreateWindow("BUTTON", "Satellite Gallery",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 500, 220, 300, 40, hwnd, (HMENU)ID_SATELLITE_MENU, hInst, NULL);
    
    CreateWindow("BUTTON", "Contact Information",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 500, 270, 300, 40, hwnd, (HMENU)ID_CONTACT_MENU, hInst, NULL);
    
    

CreateWindow("BUTTON", "Feedback / Suggestion Box",
    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
    500, 320, 300, 40, hwnd, (HMENU)ID_FEEDBACK_MENU, hInst, NULL);


    
    CreateWindow("BUTTON", "EXIT",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 500, 370, 300, 40, hwnd, (HMENU)ID_EXIT, hInst, NULL);
    
    // Footer
    CreateWindow("STATIC", "© 2025 SUPARCO - Pakistan's Gateway to Space",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 50, 630, 800, 25, hwnd, NULL, hInst, NULL);
}

// ==================== APPLICATION FORM SCREEN ====================
void showApplicationForm(HWND hwnd, const string& applicationType) {
    clearScreen(hwnd);
    
    string title = "Application Form - " + applicationType;
    CreateWindow("STATIC", title.c_str(),
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 30, hwnd, NULL, hInst, NULL);
    
    // Form Fields
    int yPos = 70;
    
    CreateWindow("STATIC", "Full Name:",
                 WS_VISIBLE | WS_CHILD,
                 100, yPos, 150, 25, hwnd, NULL, hInst, NULL);
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, yPos, 400, 25, hwnd, (HMENU)ID_EDIT_NAME, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "CNIC (13 digits):",
                 WS_VISIBLE | WS_CHILD,
                 100, yPos, 150, 25, hwnd, NULL, hInst, NULL);
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, yPos, 400, 25, hwnd, (HMENU)ID_EDIT_CNIC, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Age:",
                 WS_VISIBLE | WS_CHILD,
                 100, yPos, 150, 25, hwnd, NULL, hInst, NULL);
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, yPos, 400, 25, hwnd, (HMENU)ID_EDIT_AGE, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Email:",
                 WS_VISIBLE | WS_CHILD,
                 100, yPos, 150, 25, hwnd, NULL, hInst, NULL);
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, yPos, 400, 25, hwnd, (HMENU)ID_EDIT_EMAIL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Phone (11 digits):",
                 WS_VISIBLE | WS_CHILD,
                 100, yPos, 150, 25, hwnd, NULL, hInst, NULL);
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, yPos, 400, 25, hwnd, (HMENU)ID_EDIT_PHONE, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Education:",
                 WS_VISIBLE | WS_CHILD,
                 100, yPos, 150, 25, hwnd, NULL, hInst, NULL);
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, yPos, 400, 25, hwnd, (HMENU)ID_EDIT_EDUCATION, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Experience (years):",
                 WS_VISIBLE | WS_CHILD,
                 100, yPos, 150, 25, hwnd, NULL, hInst, NULL);
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, yPos, 400, 25, hwnd, (HMENU)ID_EDIT_EXPERIENCE, hInst, NULL);
    yPos += 40;
    
    // Role Selection based on application type
    CreateWindow("STATIC", "Select Role:",
                 WS_VISIBLE | WS_CHILD,
                 100, yPos, 150, 25, hwnd, NULL, hInst, NULL);
    
    HWND hCombo;
    if (applicationType == "Job") {
        hCombo = CreateWindow("COMBOBOX", "",
                             WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL,
                             280, yPos, 400, 200, hwnd, (HMENU)ID_COMBO_JOB_TYPE, hInst, NULL);
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Engineer");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Scientist");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Technician");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Data Analyst");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Administrator");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Project Manager");
    } else if (applicationType == "Internship") {
        hCombo = CreateWindow("COMBOBOX", "",
                             WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL,
                             280, yPos, 400, 200, hwnd, (HMENU)ID_COMBO_INTERN_TYPE, hInst, NULL);
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Engineering Intern");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Research Intern");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"GIS Intern");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Data Analyst Intern");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Software Development Intern");
    }
    
    SendMessage(hCombo, CB_SETCURSEL, 0, 0);
    
    // Buttons
    CreateWindow("BUTTON", "Submit Application",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 250, 550, 180, 40, hwnd, (HMENU)ID_BTN_SUBMIT_APP, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 470, 550, 180, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== APPLY MENU SCREEN ====================
void showApplyMenu(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "Application Type Selection",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 50, 500, 40, hwnd, NULL, hInst, NULL);
    
    CreateWindow("STATIC", "Please select the type of position you want to apply for:",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 100, 500, 30, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "Apply for Job Position",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 300, 180, 300, 50, hwnd, (HMENU)ID_BTN_JOB, hInst, NULL);
    
    CreateWindow("BUTTON", "Apply for Internship",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 300, 250, 300, 50, hwnd, (HMENU)ID_BTN_INTERNSHIP, hInst, NULL);
    
    CreateWindow("BUTTON", "Apply for Research Role",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 300, 320, 300, 50, hwnd, (HMENU)ID_BTN_RESEARCH, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 300, 400, 300, 50, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== ADMIN PANEL SCREEN ====================
void showAdminPanel(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "Admin Control Panel",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    CreateWindow("STATIC", "Manage Applications and View Statistics",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 60, 500, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "View All Applications",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 300, 130, 300, 45, hwnd, (HMENU)ID_BTN_VIEW_APPS, hInst, NULL);
    
    CreateWindow("BUTTON", "View Statistics",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 300, 190, 300, 45, hwnd, (HMENU)ID_BTN_STATS, hInst, NULL);
    
    CreateWindow("BUTTON", "Export Report",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 300, 250, 300, 45, hwnd, (HMENU)ID_BTN_EXPORT, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 300, 330, 300, 45, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== VIEW APPLICATIONS SCREEN ====================
void showViewApplications(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "All Applications",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 30, hwnd, NULL, hInst, NULL);
    
    // Listbox to display applications
    HWND hList = CreateWindow("LISTBOX", "",
                              WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
                              50, 60, 800, 400, hwnd, (HMENU)ID_LIST_APPLICATIONS, hInst, NULL);
    
    // Populate listbox
    for (int i = 0; i < totalApplications; i++) {
        string item = intToString(i + 1) + ". " + applications[i].name + 
                     " | " + applications[i].role + 
                     " | Status: " + applications[i].status;
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)item.c_str());
    }
    
    // Search by CNIC
    CreateWindow("STATIC", "Search by CNIC:",
                 WS_VISIBLE | WS_CHILD,
                 50, 480, 150, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 210, 480, 200, 25, hwnd, (HMENU)ID_EDIT_CNIC_SEARCH, hInst, NULL);
    
    CreateWindow("BUTTON", "Approve Selected",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 50, 530, 150, 35, hwnd, (HMENU)ID_BTN_APPROVE, hInst, NULL);
    
    CreateWindow("BUTTON", "Reject Selected",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 220, 530, 150, 35, hwnd, (HMENU)ID_BTN_REJECT, hInst, NULL);
    
    CreateWindow("BUTTON", "Back",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 700, 530, 150, 35, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== STATISTICS SCREEN ====================
void showStatistics(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "Application Statistics",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    // Calculate statistics
    int pending = 0, approved = 0, rejected = 0;
    int jobs = 0, internships = 0, research = 0;
    int totalAge = 0;
    
    for (int i = 0; i < totalApplications; i++) {
        if (applications[i].status == "Pending") pending++;
        else if (applications[i].status == "Approved") approved++;
        else if (applications[i].status == "Rejected") rejected++;
        
        if (applications[i].category.find("Job") != string::npos) jobs++;
        else if (applications[i].category.find("Internship") != string::npos) internships++;
        else if (applications[i].category.find("Research") != string::npos) research++;
        
        totalAge += applications[i].age;
    }
    
    double avgAge = totalApplications > 0 ? (double)totalAge / totalApplications : 0;
    
    // Display statistics
    int yPos = 80;
    
    string totalStr = "Total Applications: " + intToString(totalApplications);
    CreateWindow("STATIC", totalStr.c_str(),
                 WS_VISIBLE | WS_CHILD,
                 150, yPos, 600, 30, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== Status Breakdown ===",
                 WS_VISIBLE | WS_CHILD,
                 150, yPos, 600, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    string pendingStr = "Pending: " + intToString(pending);
    CreateWindow("STATIC", pendingStr.c_str(),
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    string approvedStr = "Approved: " + intToString(approved);
    CreateWindow("STATIC", approvedStr.c_str(),
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    string rejectedStr = "Rejected: " + intToString(rejected);
    CreateWindow("STATIC", rejectedStr.c_str(),
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== Category Breakdown ===",
                 WS_VISIBLE | WS_CHILD,
                 150, yPos, 600, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    string jobsStr = "Jobs: " + intToString(jobs);
    CreateWindow("STATIC", jobsStr.c_str(),
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    string internsStr = "Internships: " + intToString(internships);
    CreateWindow("STATIC", internsStr.c_str(),
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    string researchStr = "Research Roles: " + intToString(research);
    CreateWindow("STATIC", researchStr.c_str(),
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("BUTTON", "Back",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 350, 550, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== NEWS SCREEN ====================
void showNewsScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "SUPARCO News & Updates",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    // News Listbox
    HWND hList = CreateWindow("LISTBOX", "",
                              WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL,
                              50, 70, 800, 150, hwnd, (HMENU)ID_LIST_NEWS, hInst, NULL);
    
    SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"[2025-01-08] SUPARCO launches new satellite development program");
    SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"[2025-01-05] ICAST 2025 Conference dates announced: July 15-20");
    SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"[2025-01-03] New GIS services for agriculture monitoring launched");
    SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"[2024-12-28] SUPARCO signs MoU with international space agency");
    SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"[2024-12-20] Internship applications open for Summer 2025");
    
    // Weather Forecast Section
    CreateWindow("STATIC", "5-Day Weather Forecast (Islamabad)",
                 WS_VISIBLE | WS_CHILD,
                 50, 240, 800, 30, hwnd, NULL, hInst, NULL);
    
    int yPos = 280;
    CreateWindow("STATIC", "Day 1: Sunny, 28°C, Humidity: 45%, Wind: 10 km/h",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 700, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Day 2: Partly Cloudy, 27°C, Humidity: 50%, Wind: 12 km/h",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 700, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Day 3: Rainy, 24°C, Humidity: 70%, Wind: 15 km/h",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 700, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Day 4: Cloudy, 25°C, Humidity: 60%, Wind: 10 km/h",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 700, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Day 5: Sunny, 29°C, Humidity: 40%, Wind: 8 km/h",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 700, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 350, 550, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== ABOUT SCREEN ====================
void showAboutScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "About SUPARCO",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    int yPos = 80;
    
    CreateWindow("STATIC", "SUPARCO - Space & Upper Atmosphere Research Commission",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    CreateWindow("STATIC", "Pakistan's National Space Agency",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "Established: 1961",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Headquarters: Islamabad, Pakistan",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "Mission:",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "- Develop indigenous space technology and satellite programs",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "- Promote research in space science and technology",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "- Provide satellite-based services for national development",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "Major Divisions:",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "- Satellite Development | Remote Sensing & GIS | Space Science",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "- Communication Systems | Research & Development",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 350, 550, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== PROJECTS SCREEN ====================
void showProjectsScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "SUPARCO Projects & Services",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    int yPos = 80;
    
    CreateWindow("STATIC", "=== Satellite Programs ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "• PakSAT-1R: Communication satellite with C-band coverage (Launched: 2011)",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• PRSS-1: Remote sensing satellite with high-resolution imaging (Launched: 2018)",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• PakTES-1A: Technology demonstration satellite (Launched: 2018)",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• HS-1: Hyperspectral earth observation satellite (Upcoming Launch)",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== Education & Training Programs ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "• Workshops for students and researchers in space technology",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Internship programs in engineering, research, and GIS",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Training in satellite development and remote sensing",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== Space Weather Centre ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "• Monitors solar activity and geomagnetic storms",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Provides forecasts to protect satellites and communication systems",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 350, 600, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== RESEARCH SCREEN ====================
void showResearchScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "Research Programs",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    int yPos = 80;
    
    CreateWindow("STATIC", "=== Space Experimentation ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "• Materials testing in microgravity environments",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Physics experiments onboard satellites",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Development and testing of advanced space technologies",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== Astronomy Research ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "• Observation and study of celestial objects",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Collaborative studies with international space agencies",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Development of advanced telescopes and sensor systems",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== Microgravity Studies ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "• Plant growth experiments in space environments",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Fluid dynamics studies under low-gravity conditions",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Material science research in microgravity",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 350, 600, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== GIS SERVICES SCREEN ====================
void showGISScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "Remote Sensing & GIS Services",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    int yPos = 80;
    
    CreateWindow("STATIC", "=== Agriculture Monitoring ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "• Crop health monitoring using satellite imagery",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Irrigation and soil moisture analysis",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Planning for sustainable agriculture practices",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== Disaster Management ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "• Flood, earthquake, and storm tracking systems",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Real-time damage assessment capabilities",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Early warning systems using satellite data",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== Water Resources Monitoring ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "• River and reservoir level monitoring",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "• Water quality assessment programs",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 350, 600, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== COOPERATION SCREEN ====================
void showCooperationScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "International Cooperation",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    int yPos = 100;
    
    CreateWindow("STATIC", "SUPARCO actively collaborates with international space organizations:",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 60;
    
    CreateWindow("STATIC", "• APSCO (Asia-Pacific Space Cooperation Organization)",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    CreateWindow("STATIC", "  - Member since 2008",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "  - Collaborative satellite development programs",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "• ISNET (International Space Network)",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    CreateWindow("STATIC", "  - Data sharing and research collaboration",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "  - Joint space science missions",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "• Exchange Programs:",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    CreateWindow("STATIC", "  - Research scientist exchanges",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "  - Technology transfer programs",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "  - Joint conferences and workshops",
                 WS_VISIBLE | WS_CHILD,
                 90, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 350, 600, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== SATELLITE GALLERY SCREEN ====================
void showSatelliteScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "Satellite Gallery",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    int yPos = 80;
    
    CreateWindow("STATIC", "=== PakSAT-1R ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    CreateWindow("STATIC", "Type: Communications Satellite | Launch: August 2011",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Features: C-band coverage, telecommunication services",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== PRSS-1 ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    CreateWindow("STATIC", "Type: Remote Sensing Satellite | Launch: July 2018",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Features: High-resolution optical imaging, multi-spectral camera",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== PakTES-1A ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    CreateWindow("STATIC", "Type: Technology Demonstration | Launch: July 2018",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Features: Experimental payloads, technology testing platform",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 50;
    
    CreateWindow("STATIC", "=== HS-1 (Upcoming) ===",
                 WS_VISIBLE | WS_CHILD,
                 50, yPos, 800, 30, hwnd, NULL, hInst, NULL);
    yPos += 35;
    
    CreateWindow("STATIC", "Type: Hyperspectral Earth Observation | Launch: Planned",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Features: Advanced hyperspectral imaging for environmental monitoring",
                 WS_VISIBLE | WS_CHILD,
                 70, yPos, 800, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 350, 600, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}
