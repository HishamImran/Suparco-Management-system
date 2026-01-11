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
