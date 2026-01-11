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
