
// ==================== CONTACT SCREEN ====================
void showContactScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "Contact Information",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    int yPos = 100;
    
    CreateWindow("STATIC", "=== Headquarters ===",
                 WS_VISIBLE | WS_CHILD,
                 150, yPos, 600, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Address: Off University Road, Karachi Company, Islamabad, Pakistan",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Phone: +92-51-9248167",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Email: info@suparco.gov.pk",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 60;
    
    CreateWindow("STATIC", "=== Regional Offices ===",
                 WS_VISIBLE | WS_CHILD,
                 150, yPos, 600, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Karachi Office: Karachi Space Centre",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Lahore Office: Lahore Research Centre",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 60;
    
    CreateWindow("STATIC", "=== Office Hours ===",
                 WS_VISIBLE | WS_CHILD,
                 150, yPos, 600, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Monday - Friday: 9:00 AM - 5:00 PM",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Saturday - Sunday: Closed",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 350, 550, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== FEEDBACK SCREEN ====================
void showFeedbackScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "Feedback / Suggestion Box",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    CreateWindow("STATIC", "Your Name:",
                 WS_VISIBLE | WS_CHILD,
                 100, 80, 150, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, 80, 400, 25, hwnd, (HMENU)ID_EDIT_FEEDBACK_NAME, hInst, NULL);
    
    CreateWindow("STATIC", "Your Email:",
                 WS_VISIBLE | WS_CHILD,
                 100, 120, 150, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, 120, 400, 25, hwnd, (HMENU)ID_EDIT_FEEDBACK_EMAIL, hInst, NULL);
    
    CreateWindow("STATIC", "Rating (1-5):",
                 WS_VISIBLE | WS_CHILD,
                 100, 160, 150, 25, hwnd, NULL, hInst, NULL);
    
    HWND hCombo = CreateWindow("COMBOBOX", "",
                               WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
                               280, 160, 400, 150, hwnd, (HMENU)ID_COMBO_RATING, hInst, NULL);
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"5 - Excellent");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"4 - Very Good");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"3 - Good");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"2 - Fair");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"1 - Poor");
    SendMessage(hCombo, CB_SETCURSEL, 0, 0);
    
    CreateWindow("STATIC", "Your Feedback/Suggestion:",
                 WS_VISIBLE | WS_CHILD,
                 100, 210, 600, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                 100, 240, 700, 250, hwnd, (HMENU)ID_EDIT_FEEDBACK, hInst, NULL);
    
    
CreateWindow("BUTTON", "Submit Feedback",
    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
    250, 520, 180, 40, hwnd, (HMENU)ID_BTN_SUBMIT_FEEDBACK, hInst, NULL);

    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 470, 520, 180, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== MAIN WINDOW PROCEDURE ====================
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            loadPasswordsFromFile();
            if (!isPasswordSet) {
                showPasswordSetupScreen(hwnd);
            } else {
                showMainMenu(hwnd);
            }
            break;
            
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Set background color
            HBRUSH hBrush = CreateSolidBrush(COLOR_BG);
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);
            
            EndPaint(hwnd, &ps);
            break;
        }
        
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            
            // Password Setup
            if (wmId == ID_PASSWORD_SETUP) {
                char buffer1[256], buffer2[256];
                GetDlgItemText(hwnd, ID_EDIT_PASSWORD, buffer1, 256);
                GetDlgItemText(hwnd, ID_EDIT_PASSWORD + 1, buffer2, 256);
                
                string pass1(buffer1);
                string pass2(buffer2);
                string errorMsg;
                
                if (!validatePassword(pass1, errorMsg)) {
                    MessageBox(hwnd, errorMsg.c_str(), "Admin Password Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (!validatePassword(pass2, errorMsg)) {
                    MessageBox(hwnd, errorMsg.c_str(), "Secret Password Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                adminPassword = pass1;
                secretPassword = pass2;
                isPasswordSet = true;
                savePasswordsToFile();
                
                MessageBox(hwnd, "Passwords set successfully!", "Success", MB_OK | MB_ICONINFORMATION);
                showMainMenu(hwnd);
            }
            
            // Main Menu Navigation
            else if (wmId == ID_APPLY_MENU) {
                showApplyMenu(hwnd);
            }
            
else if (wmId == ID_ADMIN_MENU) {
    // Build a simple inline login screen (no modal traps)
    clearScreen(hwnd);

    CreateWindow("STATIC", "Enter Admin Password:",
        WS_VISIBLE | WS_CHILD, 280, 260, 200, 25, hwnd, NULL, hInst, NULL);

    HWND hPwd = CreateWindow("EDIT", "",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD | WS_TABSTOP,
        280, 290, 300, 25, hwnd, (HMENU)9999, hInst, NULL);

    CreateWindow("BUTTON", "Login",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
        590, 288, 80, 30, hwnd, (HMENU)ID_BTN_ADMIN_LOGIN, hInst, NULL);

    CreateWindow("BUTTON", "Back to Main Menu",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
        350, 330, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);

    SetFocus(hPwd);
        
}

else if (wmId == ID_BTN_ADMIN_LOGIN) {
    char buffer[256]{};
    GetDlgItemText(hwnd, 9999, buffer, 256);

    if (string(buffer).empty()) {
        MessageBox(hwnd, "Please enter the password.", "Admin Login", MB_OK | MB_ICONWARNING);
        SetFocus(GetDlgItem(hwnd, 9999));
        break;
    }

    if (string(buffer) == adminPassword) {
        showAdminPanel(hwnd);
    } else {
        MessageBox(hwnd, "Wrong Password!", "Error", MB_OK | MB_ICONERROR);
        SetFocus(GetDlgItem(hwnd, 9999)); // let user retry
    }
}

                
            
                        
            else if (wmId == ID_NEWS_MENU) {
                showNewsScreen(hwnd);
            }
            else if (wmId == ID_ABOUT_MENU) {
                showAboutScreen(hwnd);
            }
            else if (wmId == ID_PROJECTS_MENU) {
                showProjectsScreen(hwnd);
            }
            else if (wmId == ID_RESEARCH_MENU) {
                showResearchScreen(hwnd);
            }
            else if (wmId == ID_GIS_MENU) {
                showGISScreen(hwnd);
            }
            else if (wmId == ID_COOPERATION_MENU) {
                showCooperationScreen(hwnd);
            }
            else if (wmId == ID_SATELLITE_MENU) {
                showSatelliteScreen(hwnd);
            }
            else if (wmId == ID_CONTACT_MENU) {
                showContactScreen(hwnd);
            }
            else if (wmId == ID_FEEDBACK_MENU) {
                showFeedbackScreen(hwnd);
            }
            
            // Application Type Selection
            else if (wmId == ID_BTN_JOB) {
                showApplicationForm(hwnd, "Job");
            }
            else if (wmId == ID_BTN_INTERNSHIP) {
                showApplicationForm(hwnd, "Internship");
            }
            else if (wmId == ID_BTN_RESEARCH) {
                showApplicationForm(hwnd, "Research");
            }
            
            // Submit Application
            else if (wmId == ID_BTN_SUBMIT_APP) {
                if (totalApplications >= MAX_APPLICATIONS) {
                    MessageBox(hwnd, "Application limit reached!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                char buffer[256];
                Applicant newApp;
                
                GetDlgItemText(hwnd, ID_EDIT_NAME, buffer, 256);
                newApp.name = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_CNIC, buffer, 256);
                newApp.cnic = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_AGE, buffer, 256);
                newApp.age = stringToInt(string(buffer));
                
                GetDlgItemText(hwnd, ID_EDIT_EMAIL, buffer, 256);
                newApp.email = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_PHONE, buffer, 256);
                newApp.phone = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_EDUCATION, buffer, 256);
                newApp.education = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_EXPERIENCE, buffer, 256);
                newApp.experience = string(buffer);
                
                // Validation
                if (newApp.name.empty()) {
                    MessageBox(hwnd, "Please enter your name!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (!validateCNIC(newApp.cnic)) {
                    MessageBox(hwnd, "Invalid CNIC! Must be 13 digits.", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (newApp.age < 18) {
                    MessageBox(hwnd, "Age must be 18 or above!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (!validateEmail(newApp.email)) {
                    MessageBox(hwnd, "Invalid email format!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (!validatePhone(newApp.phone)) {
                    MessageBox(hwnd, "Invalid phone number! Must be 11 digits.", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                // Get role from combobox
                HWND hCombo = GetDlgItem(hwnd, ID_COMBO_JOB_TYPE);
                if (hCombo == NULL) {
                    hCombo = GetDlgItem(hwnd, ID_COMBO_INTERN_TYPE);
                }
                
                if (hCombo != NULL) {
                    int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
                    if (index != CB_ERR) {
                        char roleBuffer[256];
                        SendMessage(hCombo, CB_GETLBTEXT, index, (LPARAM)roleBuffer);
                        newApp.role = string(roleBuffer);
                        
                        // Set category based on role
                        if (newApp.role.find("Intern") != string::npos) {
                            newApp.category = "Internship - " + newApp.role;
                        } else if (newApp.role == "Researcher") {
                            newApp.category = "Research Role";
                        } else {
                            newApp.category = "Job - " + newApp.role;
                        }
                    }
                }
                
                newApp.status = "Pending";
                newApp.applicationDate = getCurrentDateTime();
                
                applications[totalApplications] = newApp;
                totalApplications++;
                
                saveApplicationToFile(newApp);
                
                MessageBox(hwnd, "Application submitted successfully!", "Success", MB_OK | MB_ICONINFORMATION);
                showMainMenu(hwnd);
            }
            
            // Submit Feedback
            else if (wmId == ID_BTN_SUBMIT_FEEDBACK) {
                if (totalFeedbacks >= 50) {
                    MessageBox(hwnd, "Feedback limit reached!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                char buffer[1024];
                Feedback newFeedback;
                
                GetDlgItemText(hwnd, ID_EDIT_FEEDBACK_NAME, buffer, 256);
                newFeedback.name = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_FEEDBACK_EMAIL, buffer, 256);
                newFeedback.email = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_FEEDBACK, buffer, 1024);
                newFeedback.message = string(buffer);
                
                HWND hCombo = GetDlgItem(hwnd, ID_COMBO_RATING);
                int ratingIndex = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
                newFeedback.rating = 5 - ratingIndex;
                
                newFeedback.date = getCurrentDateTime();
                
                if (newFeedback.name.empty() || newFeedback.message.empty()) {
                    MessageBox(hwnd, "Please fill all fields!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (!validateEmail(newFeedback.email)) {
                    MessageBox(hwnd, "Invalid email format!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                feedbacks[totalFeedbacks] = newFeedback;
                totalFeedbacks++;
                
                saveFeedbackToFile(newFeedback);
                
                MessageBox(hwnd, "Thank you for your feedback!", "Success", MB_OK | MB_ICONINFORMATION);
                showMainMenu(hwnd);
            }
            
            // Admin Panel Actions
            else if (wmId == ID_BTN_VIEW_APPS) {
                if (totalApplications == 0) {
                    MessageBox(hwnd, "No applications submitted yet!", "Info", MB_OK | MB_ICONINFORMATION);
                } else {
                    showViewApplications(hwnd);
                }
            }
            else if (wmId == ID_BTN_STATS) {
                if (totalApplications == 0) {
                    MessageBox(hwnd, "No applications to show statistics for!", "Info", MB_OK | MB_ICONINFORMATION);
                } else {
                    showStatistics(hwnd);
                }
            }
            else if (wmId == ID_BTN_EXPORT) {
                if (totalApplications == 0) {
                    MessageBox(hwnd, "No data to export!", "Info", MB_OK | MB_ICONINFORMATION);
                } else {
                    exportStatistics();
                }
            }
            
            // Approve/Reject from View Applications
            else if (wmId == ID_BTN_APPROVE || wmId == ID_BTN_REJECT) {
                HWND hList = GetDlgItem(hwnd, ID_LIST_APPLICATIONS);
                int selectedIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
                
                if (selectedIndex == LB_ERR) {
                    MessageBox(hwnd, "Please select an application first!", "Error", MB_OK | MB_ICONERROR);
                } else {
                    if (wmId == ID_BTN_APPROVE) {
                        applications[selectedIndex].status = "Approved";
                        MessageBox(hwnd, "Application approved!", "Success", MB_OK | MB_ICONINFORMATION);
                    } else {
                        applications[selectedIndex].status = "Rejected";
                        MessageBox(hwnd, "Application rejected!", "Success", MB_OK | MB_ICONINFORMATION);
                    }
                    showViewApplications(hwnd);
                }
            }
            
            // Back Button
            else if (wmId == ID_BTN_BACK) {
                showMainMenu(hwnd);
            }
            
            // Exit
            else if (wmId == ID_EXIT) {
                if (MessageBox(hwnd, "Are you sure you want to exit?", "Confirm Exit", 
                              MB_YESNO | MB_ICONQUESTION) == IDYES) {
                    PostQuitMessage(0);
                }
            }
            
            break;
        }
        
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
            
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    
    return 0;
}

// ==================== MAIN FUNCTION ====================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;
    
    // Register window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "SUPARCOManagementSystem";
    wc.hbrBackground = CreateSolidBrush(COLOR_BG);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    // Create main window
    hwndMain = CreateWindowEx(
        0,
        "SUPARCOManagementSystem",
        "SUPARCO Management System - v1.0",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL
    );
    
    if (hwndMain == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);
    
    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
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
// ==================== CONTACT SCREEN ====================
void showContactScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "Contact Information",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    int yPos = 100;
    
    CreateWindow("STATIC", "=== Headquarters ===",
                 WS_VISIBLE | WS_CHILD,
                 150, yPos, 600, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Address: Off University Road, Karachi Company, Islamabad, Pakistan",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Phone: +92-51-9248167",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Email: info@suparco.gov.pk",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 60;
    
    CreateWindow("STATIC", "=== Regional Offices ===",
                 WS_VISIBLE | WS_CHILD,
                 150, yPos, 600, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Karachi Office: Karachi Space Centre",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Lahore Office: Lahore Research Centre",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 60;
    
    CreateWindow("STATIC", "=== Office Hours ===",
                 WS_VISIBLE | WS_CHILD,
                 150, yPos, 600, 30, hwnd, NULL, hInst, NULL);
    yPos += 40;
    
    CreateWindow("STATIC", "Monday - Friday: 9:00 AM - 5:00 PM",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    yPos += 30;
    
    CreateWindow("STATIC", "Saturday - Sunday: Closed",
                 WS_VISIBLE | WS_CHILD,
                 170, yPos, 600, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 350, 550, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== FEEDBACK SCREEN ====================
void showFeedbackScreen(HWND hwnd) {
    clearScreen(hwnd);
    
    CreateWindow("STATIC", "Feedback / Suggestion Box",
                 WS_VISIBLE | WS_CHILD | SS_CENTER,
                 200, 20, 500, 35, hwnd, NULL, hInst, NULL);
    
    CreateWindow("STATIC", "Your Name:",
                 WS_VISIBLE | WS_CHILD,
                 100, 80, 150, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, 80, 400, 25, hwnd, (HMENU)ID_EDIT_FEEDBACK_NAME, hInst, NULL);
    
    CreateWindow("STATIC", "Your Email:",
                 WS_VISIBLE | WS_CHILD,
                 100, 120, 150, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                 280, 120, 400, 25, hwnd, (HMENU)ID_EDIT_FEEDBACK_EMAIL, hInst, NULL);
    
    CreateWindow("STATIC", "Rating (1-5):",
                 WS_VISIBLE | WS_CHILD,
                 100, 160, 150, 25, hwnd, NULL, hInst, NULL);
    
    HWND hCombo = CreateWindow("COMBOBOX", "",
                               WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
                               280, 160, 400, 150, hwnd, (HMENU)ID_COMBO_RATING, hInst, NULL);
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"5 - Excellent");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"4 - Very Good");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"3 - Good");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"2 - Fair");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"1 - Poor");
    SendMessage(hCombo, CB_SETCURSEL, 0, 0);
    
    CreateWindow("STATIC", "Your Feedback/Suggestion:",
                 WS_VISIBLE | WS_CHILD,
                 100, 210, 600, 25, hwnd, NULL, hInst, NULL);
    
    CreateWindow("EDIT", "",
                 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                 100, 240, 700, 250, hwnd, (HMENU)ID_EDIT_FEEDBACK, hInst, NULL);
    
    
CreateWindow("BUTTON", "Submit Feedback",
    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
    250, 520, 180, 40, hwnd, (HMENU)ID_BTN_SUBMIT_FEEDBACK, hInst, NULL);

    
    CreateWindow("BUTTON", "Back to Main Menu",
                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 470, 520, 180, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);
}

// ==================== MAIN WINDOW PROCEDURE ====================
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            loadPasswordsFromFile();
            if (!isPasswordSet) {
                showPasswordSetupScreen(hwnd);
            } else {
                showMainMenu(hwnd);
            }
            break;
            
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Set background color
            HBRUSH hBrush = CreateSolidBrush(COLOR_BG);
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);
            
            EndPaint(hwnd, &ps);
            break;
        }
        
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            
            // Password Setup
            if (wmId == ID_PASSWORD_SETUP) {
                char buffer1[256], buffer2[256];
                GetDlgItemText(hwnd, ID_EDIT_PASSWORD, buffer1, 256);
                GetDlgItemText(hwnd, ID_EDIT_PASSWORD + 1, buffer2, 256);
                
                string pass1(buffer1);
                string pass2(buffer2);
                string errorMsg;
                
                if (!validatePassword(pass1, errorMsg)) {
                    MessageBox(hwnd, errorMsg.c_str(), "Admin Password Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (!validatePassword(pass2, errorMsg)) {
                    MessageBox(hwnd, errorMsg.c_str(), "Secret Password Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                adminPassword = pass1;
                secretPassword = pass2;
                isPasswordSet = true;
                savePasswordsToFile();
                
                MessageBox(hwnd, "Passwords set successfully!", "Success", MB_OK | MB_ICONINFORMATION);
                showMainMenu(hwnd);
            }
            
            // Main Menu Navigation
            else if (wmId == ID_APPLY_MENU) {
                showApplyMenu(hwnd);
            }
            
else if (wmId == ID_ADMIN_MENU) {
    // Build a simple inline login screen (no modal traps)
    clearScreen(hwnd);

    CreateWindow("STATIC", "Enter Admin Password:",
        WS_VISIBLE | WS_CHILD, 280, 260, 200, 25, hwnd, NULL, hInst, NULL);

    HWND hPwd = CreateWindow("EDIT", "",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD | WS_TABSTOP,
        280, 290, 300, 25, hwnd, (HMENU)9999, hInst, NULL);

    CreateWindow("BUTTON", "Login",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
        590, 288, 80, 30, hwnd, (HMENU)ID_BTN_ADMIN_LOGIN, hInst, NULL);

    CreateWindow("BUTTON", "Back to Main Menu",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
        350, 330, 200, 40, hwnd, (HMENU)ID_BTN_BACK, hInst, NULL);

    SetFocus(hPwd);
        
}

else if (wmId == ID_BTN_ADMIN_LOGIN) {
    char buffer[256]{};
    GetDlgItemText(hwnd, 9999, buffer, 256);

    if (string(buffer).empty()) {
        MessageBox(hwnd, "Please enter the password.", "Admin Login", MB_OK | MB_ICONWARNING);
        SetFocus(GetDlgItem(hwnd, 9999));
        break;
    }

    if (string(buffer) == adminPassword) {
        showAdminPanel(hwnd);
    } else {
        MessageBox(hwnd, "Wrong Password!", "Error", MB_OK | MB_ICONERROR);
        SetFocus(GetDlgItem(hwnd, 9999)); // let user retry
    }
}

                
            
                        
            else if (wmId == ID_NEWS_MENU) {
                showNewsScreen(hwnd);
            }
            else if (wmId == ID_ABOUT_MENU) {
                showAboutScreen(hwnd);
            }
            else if (wmId == ID_PROJECTS_MENU) {
                showProjectsScreen(hwnd);
            }
            else if (wmId == ID_RESEARCH_MENU) {
                showResearchScreen(hwnd);
            }
            else if (wmId == ID_GIS_MENU) {
                showGISScreen(hwnd);
            }
            else if (wmId == ID_COOPERATION_MENU) {
                showCooperationScreen(hwnd);
            }
            else if (wmId == ID_SATELLITE_MENU) {
                showSatelliteScreen(hwnd);
            }
            else if (wmId == ID_CONTACT_MENU) {
                showContactScreen(hwnd);
            }
            else if (wmId == ID_FEEDBACK_MENU) {
                showFeedbackScreen(hwnd);
            }
            
            // Application Type Selection
            else if (wmId == ID_BTN_JOB) {
                showApplicationForm(hwnd, "Job");
            }
            else if (wmId == ID_BTN_INTERNSHIP) {
                showApplicationForm(hwnd, "Internship");
            }
            else if (wmId == ID_BTN_RESEARCH) {
                showApplicationForm(hwnd, "Research");
            }
            
            // Submit Application
            else if (wmId == ID_BTN_SUBMIT_APP) {
                if (totalApplications >= MAX_APPLICATIONS) {
                    MessageBox(hwnd, "Application limit reached!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                char buffer[256];
                Applicant newApp;
                
                GetDlgItemText(hwnd, ID_EDIT_NAME, buffer, 256);
                newApp.name = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_CNIC, buffer, 256);
                newApp.cnic = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_AGE, buffer, 256);
                newApp.age = stringToInt(string(buffer));
                
                GetDlgItemText(hwnd, ID_EDIT_EMAIL, buffer, 256);
                newApp.email = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_PHONE, buffer, 256);
                newApp.phone = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_EDUCATION, buffer, 256);
                newApp.education = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_EXPERIENCE, buffer, 256);
                newApp.experience = string(buffer);
                
                // Validation
                if (newApp.name.empty()) {
                    MessageBox(hwnd, "Please enter your name!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (!validateCNIC(newApp.cnic)) {
                    MessageBox(hwnd, "Invalid CNIC! Must be 13 digits.", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (newApp.age < 18) {
                    MessageBox(hwnd, "Age must be 18 or above!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (!validateEmail(newApp.email)) {
                    MessageBox(hwnd, "Invalid email format!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (!validatePhone(newApp.phone)) {
                    MessageBox(hwnd, "Invalid phone number! Must be 11 digits.", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                // Get role from combobox
                HWND hCombo = GetDlgItem(hwnd, ID_COMBO_JOB_TYPE);
                if (hCombo == NULL) {
                    hCombo = GetDlgItem(hwnd, ID_COMBO_INTERN_TYPE);
                }
                
                if (hCombo != NULL) {
                    int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
                    if (index != CB_ERR) {
                        char roleBuffer[256];
                        SendMessage(hCombo, CB_GETLBTEXT, index, (LPARAM)roleBuffer);
                        newApp.role = string(roleBuffer);
                        
                        // Set category based on role
                        if (newApp.role.find("Intern") != string::npos) {
                            newApp.category = "Internship - " + newApp.role;
                        } else if (newApp.role == "Researcher") {
                            newApp.category = "Research Role";
                        } else {
                            newApp.category = "Job - " + newApp.role;
                        }
                    }
                }
                
                newApp.status = "Pending";
                newApp.applicationDate = getCurrentDateTime();
                
                applications[totalApplications] = newApp;
                totalApplications++;
                
                saveApplicationToFile(newApp);
                
                MessageBox(hwnd, "Application submitted successfully!", "Success", MB_OK | MB_ICONINFORMATION);
                showMainMenu(hwnd);
            }
            
            // Submit Feedback
            else if (wmId == ID_BTN_SUBMIT_FEEDBACK) {
                if (totalFeedbacks >= 50) {
                    MessageBox(hwnd, "Feedback limit reached!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                char buffer[1024];
                Feedback newFeedback;
                
                GetDlgItemText(hwnd, ID_EDIT_FEEDBACK_NAME, buffer, 256);
                newFeedback.name = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_FEEDBACK_EMAIL, buffer, 256);
                newFeedback.email = string(buffer);
                
                GetDlgItemText(hwnd, ID_EDIT_FEEDBACK, buffer, 1024);
                newFeedback.message = string(buffer);
                
                HWND hCombo = GetDlgItem(hwnd, ID_COMBO_RATING);
                int ratingIndex = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
                newFeedback.rating = 5 - ratingIndex;
                
                newFeedback.date = getCurrentDateTime();
                
                if (newFeedback.name.empty() || newFeedback.message.empty()) {
                    MessageBox(hwnd, "Please fill all fields!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                if (!validateEmail(newFeedback.email)) {
                    MessageBox(hwnd, "Invalid email format!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                
                feedbacks[totalFeedbacks] = newFeedback;
                totalFeedbacks++;
                
                saveFeedbackToFile(newFeedback);
                
                MessageBox(hwnd, "Thank you for your feedback!", "Success", MB_OK | MB_ICONINFORMATION);
                showMainMenu(hwnd);
            }
            
            // Admin Panel Actions
            else if (wmId == ID_BTN_VIEW_APPS) {
                if (totalApplications == 0) {
                    MessageBox(hwnd, "No applications submitted yet!", "Info", MB_OK | MB_ICONINFORMATION);
                } else {
                    showViewApplications(hwnd);
                }
            }
            else if (wmId == ID_BTN_STATS) {
                if (totalApplications == 0) {
                    MessageBox(hwnd, "No applications to show statistics for!", "Info", MB_OK | MB_ICONINFORMATION);
                } else {
                    showStatistics(hwnd);
                }
            }
            else if (wmId == ID_BTN_EXPORT) {
                if (totalApplications == 0) {
                    MessageBox(hwnd, "No data to export!", "Info", MB_OK | MB_ICONINFORMATION);
                } else {
                    exportStatistics();
                }
            }
            
            // Approve/Reject from View Applications
            else if (wmId == ID_BTN_APPROVE || wmId == ID_BTN_REJECT) {
                HWND hList = GetDlgItem(hwnd, ID_LIST_APPLICATIONS);
                int selectedIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
                
                if (selectedIndex == LB_ERR) {
                    MessageBox(hwnd, "Please select an application first!", "Error", MB_OK | MB_ICONERROR);
                } else {
                    if (wmId == ID_BTN_APPROVE) {
                        applications[selectedIndex].status = "Approved";
                        MessageBox(hwnd, "Application approved!", "Success", MB_OK | MB_ICONINFORMATION);
                    } else {
                        applications[selectedIndex].status = "Rejected";
                        MessageBox(hwnd, "Application rejected!", "Success", MB_OK | MB_ICONINFORMATION);
                    }
                    showViewApplications(hwnd);
                }
            }
            
            // Back Button
            else if (wmId == ID_BTN_BACK) {
                showMainMenu(hwnd);
            }
            
            // Exit
            else if (wmId == ID_EXIT) {
                if (MessageBox(hwnd, "Are you sure you want to exit?", "Confirm Exit", 
                              MB_YESNO | MB_ICONQUESTION) == IDYES) {
                    PostQuitMessage(0);
                }
            }
            
            break;
        }
        
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
            
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    
    return 0;
}

// ==================== MAIN FUNCTION ====================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;
    
    // Register window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "SUPARCOManagementSystem";
    wc.hbrBackground = CreateSolidBrush(COLOR_BG);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    // Create main window
    hwndMain = CreateWindowEx(
        0,
        "SUPARCOManagementSystem",
        "SUPARCO Management System - v1.0",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL
    );
    
    if (hwndMain == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);
    
    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}

