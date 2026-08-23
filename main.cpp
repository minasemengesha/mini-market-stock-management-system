#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>
using namespace std;

// --- Function Prototypes ---
bool authenticateUser(string role, string correctUser, string correctPass);
void handleOwnerDashboard(bool &isLoggedIn);
void handleAccountantDashboard(bool &isLoggedIn);
bool authenticateExternalPaymentSystem();
void handleHelpMenu();

// --- Owner and Accountant Functions Prototypes ---
void handleAddStock();
void handleAddStockToFile();
void handleUpdateStock();
void handleDeleteStock();
void handleRecordSales();
void handleViewStock();
void handleAddProduct();
void handleUpdateProduct();
void handleDeleteProduct();
void handleViewReport();
void handleViewLowStockAlert();
void handleViewExpiryAlert();
void handleGenerateReport();
void handleCheckIncomeAndCost();

// --- External System Function Prototypes ---
void handlePaymentIntegration();

// --- Function for External Payment Integration Simulation ---
void handlePaymentIntegration() {
    double amount;
    string phoneNumber;
    int paymentProvider;

    cout << "\n=========================================\n";
    cout << "        External Payment Integration     \n";
    cout << "=========================================\n";
    cout << " Select Payment Gateway / Provider:\n";
    cout << " 1. Telebirr\n";
    cout << " 2. CBE Birr\n";
    cout << " 3. Chapa Payment Gateway\n";
    cout << "Enter choice (1-3): ";
    cin >> paymentProvider;

    if (paymentProvider < 1 || paymentProvider > 3) {
        cout << "\n[Error] Invalid payment provider selected!\n";
        return;
    }

    string providerName = "";
    if (paymentProvider == 1) providerName = "Telebirr";
    else if (paymentProvider == 2) providerName = "CBE Birr";
    else if (paymentProvider == 3) providerName = "Chapa";

    cout << "Enter Customer Phone Number / Account: ";
    cin >> phoneNumber;

    // የክፍያ መጠን ማረጋገጫ
    while (true) {
        cout << "Enter Amount to Pay (ETB): ";
        cin >> amount;
        if (amount <= 0) {
            cout << "\n[Error] Invalid amount! Must be greater than 0. Try again.\n";
        } else {
            break;
        }
    }

    cout << "\n[API Request] Connecting to " << providerName << " External Gateway...\n";
    cout << "[Processing] Sending payment request of " << amount << " ETB for " << phoneNumber << "...\n";
    cout << "[Waiting] Awaiting customer PIN approval from external system...\n";

    // ከውጪ ሲስተም የሚመጣውን ልዩ የግብይት መለያ (Transaction ID/Reference) በዘፈቀደ ማመንጨት
    srand(time(0));
    int randomId = 100000 + rand() % 900000;
    string transactionRef = "TXN-" + providerName.substr(0, 3) + "-" + to_string(randomId);

    // የክፍያ ስኬት ማረጋገጫ ከውጪው ሲስተም መመለሱን ማሳየት
    cout << "\n=========================================\n";
    cout << " [SUCCESS] External Payment Verified & Approved!\n";
    cout << "-----------------------------------------\n";
    cout << " - Gateway Provider     : " << providerName << "\n";
    cout << " - Transaction Reference: " << transactionRef << "\n";
    cout << " - Paid Amount          : " << amount << " ETB\n";
    cout << " - Account/Phone        : " << phoneNumber << "\n";
    cout << " - Status               : Completed Successfully\n";
    cout << "=========================================\n";
}

// --- Function to Added Stock to Save to File ---
void handleAddStockToFile() {
    string stockName;
    int quantity;
    string expiryDate;
    string currentDate = "2026-08-22";

    cout << "\n--- Add Stock & Save to File ---\n";
    cout << "Enter Item Name: ";
    cin >> stockName;

    while (true) {
        cout << "Enter Quantity: ";
        cin >> quantity;
        if (quantity <= 0) {
            cout << "\n[Error] Invalid Quantity! Must be greater than 0. Try again.\n";
        } else {
            break;
        }
    }

    while (true) {
        cout << "Enter Expiry Date (YYYY-MM-DD): ";
        cin >> expiryDate;
        if (expiryDate < currentDate) {
            cout << "\n[Error] Invalid Expiry Date! Cannot add expired stock. Try again.\n";
        } else {
            break;
        }
    }

    ofstream outFile("stock_data.txt", ios::app);

    if (outFile.is_open()) {
        outFile << stockName << "," << quantity << "," << expiryDate << "\n";
        outFile.close();
        cout << "\n[Success] Stock saved to 'stock_data.txt' file successfully!\n";
    } else {
        cout << "\n[Error] Unable to open file for writing!\n";
    }
}

// --- Function to Record Sales (Reads Stock, Validates Quantity, and Updates File) ---
void handleRecordSales() {
    string stockName;
    int soldQuantity;

    cout << "\n--- Record Sales ---\n";
    cout << "Enter Item Name to Sell: ";
    cin >> stockName;

    // ፋይሉን አንብብን እቃውን መፈለግ
    ifstream inFile("stock_data.txt");
    ofstream outFile("temp.txt"); // አዲሱን የተስተካከለ ስቶክ ለመያዝ ጊዜያዊ ፋይል

    bool found = false;
    bool sufficientStock = false;
    string line;

    if (inFile.is_open() && outFile.is_open()) {
        while (getline(inFile, line)) {
            size_t commaPos1 = line.find(',');
            size_t commaPos2 = line.find(',', commaPos1 + 1);

            if (commaPos1 != string::npos && commaPos2 != string::npos) {
                string savedName = line.substr(0, commaPos1);
                int savedQuantity = stoi(line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1));
                string savedExpiry = line.substr(commaPos2 + 1);

                if (savedName == stockName) {
                    found = true;

                    cout << "Current Available Quantity for '" << stockName << "': " << savedQuantity << "\n";

                    // የሽያጭ ብዛት ማረጋገጫ
                    while (true) {
                        cout << "Enter Quantity to Sell: ";
                        cin >> soldQuantity;

                        if (soldQuantity <= 0) {
                            cout << "\n[Error] Invalid quantity! Must be greater than 0.\n";
                        } else if (soldQuantity > savedQuantity) {
                            cout << "\n[Error] Not enough stock available! Only " << savedQuantity << " units left. Try again.\n";
                        } else {
                            sufficientStock = true;
                            break;
                        }
                    }

                    // ከተረፈው ስቶክ ላይ ተቀንሶ አዲሱ መጠን ይቀመጣል
                    int remainingQuantity = savedQuantity - soldQuantity;

                    // የቀረው ስቶክ ከ 0 በላይ ከሆነ በፋይሉ ውስጥ እናዘምነዋለን (ብዛቱ 0 ከሆነ ፋይል ውስጥ እንዳይጻፍ መተውም ይቻላል)
                    if (remainingQuantity > 0) {
                        outFile << savedName << "," << remainingQuantity << "," << savedExpiry << "\n";
                    }

                    cout << "\n[Success] Sold " << soldQuantity << " units of '" << stockName << "' successfully!\n";
                    cout << " - Remaining Stock for '" << stockName << "': " << remainingQuantity << "\n";
                } else {
                    // ሌሎቹን ያልተነኩ እቃዎች እንዳሉ ወደ ጊዜያዊ ፋይሉ እንገልብጣቸዋለን
                    outFile << line << "\n";
                }
            }
        }
        inFile.close();
        outFile.close();

        // ዋናውን ፋይል ሰርዘን በጊዜያዊው ፋይል እንተካዋለን (Replace)
        remove("stock_data.txt");
        rename("temp.txt", "stock_data.txt");

    } else {
        cout << "\n[Error] Unable to open stock file!\n";
        return;
    }

    if (!found) {
        cout << "\n[Error] Item '" << stockName << "' not found in stock database!\n";
        // ፋይሎቹ ከተሳሳቱ እንዳይበላሹ ጊዜያዊውን እናጸዳለን
        remove("temp.txt");
    }
}

// --- Function to View Stock (Reads and Displays from File) ---
void handleViewStock() {
    ifstream inFile("stock_data.txt");
    string line;
    int itemCount = 0;

    cout << "\n=========================================\n";
    cout << "          Current Stock List             \n";
    cout << "=========================================\n";

    if (inFile.is_open()) {
        // ፋይሉ ባዶ መሆኑን ወይም አለመሆኑን ማረጋገጥ
        if (inFile.peek() == ifstream::traits_type::eof()) {
            cout << " [Info] The stock is currently empty! No items found.\n";
        } else {
            cout << "No. | Item Name       | Quantity | Expiry Date\n";
            cout << "-----------------------------------------\n";

            while (getline(inFile, line)) {
                size_t commaPos1 = line.find(',');
                size_t commaPos2 = line.find(',', commaPos1 + 1);

                if (commaPos1 != string::npos && commaPos2 != string::npos) {
                    string stockName = line.substr(0, commaPos1);
                    string quantity = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
                    string expiryDate = line.substr(commaPos2 + 1);

                    itemCount++;
                    cout << " " << itemCount << ".  | "
                         << stockName << "\t\t| "
                         << quantity << "\t | "
                         << expiryDate << "\n";
                }
            }
        }
        inFile.close();
    } else {
        cout << " [Error] Could not open stock data file or file doesn't exist yet!\n";
        cout << " (Tip: Try adding some stock first using the 'Add Stock' option.)\n";
    }
    cout << "=========================================\n";
}

// --- Function to Add Product and Save to File ---
void handleAddProduct() {
    string productName, productType, productDescription, expiryDate;
    double costPrice, sellingPrice;
    string currentDate = "2026-08-23"; // የአሁን ጊዜ ማመሳከሪያ

    cout << "\n--- Add New Product (Detailed) ---\n";

    // ከዚህ ቀደም የነበረውን የኢንፑት ማህደረ ትውስታ (Buffer) ለማጽዳት
    cin.ignore();

    cout << "Enter Product Name: ";
    getline(cin, productName);

    cout << "Enter Product Type / Category: ";
    getline(cin, productType);

    cout << "Enter Product Description: ";
    getline(cin, productDescription);

    // የግዢ ዋጋ (Cost Price) ማረጋገጫ
    while (true) {
        cout << "Enter Cost Price: ";
        cin >> costPrice;
        if (costPrice <= 0) {
            cout << "\n[Error] Invalid Cost Price! Must be greater than 0. Try again.\n";
        } else {
            break;
        }
    }

    // የመሸጫ ዋጋ (Selling Price) ማረጋገጫ
    while (true) {
        cout << "Enter Selling Price: ";
        cin >> sellingPrice;
        if (sellingPrice <= 0) {
            cout << "\n[Error] Invalid Selling Price! Must be greater than 0. Try again.\n";
        } else if (sellingPrice < costPrice) {
            cout << "\n[Warning] Selling price is less than cost price! (You might incur a loss).\n";
            cout << "Do you want to re-enter? (1. Yes / 2. No): ";
            int choice;
            cin >> choice;
            if (choice == 1) {
                continue;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    // የማብቂያ ቀን (Expiry Date) ማረጋገጫ
    while (true) {
        cout << "Enter Product Expiry Date (YYYY-MM-DD): ";
        cin >> expiryDate;
        if (expiryDate < currentDate) {
            cout << "\n[Error] Invalid Expiry Date! Date is already in the past. Try again.\n";
        } else {
            break;
        }
    }

    // መረጃውን በ CSV (Comma Separated Values) መልክ 'product_data.txt' ፋይል ውስጥ ማስቀመጥ
    ofstream outFile("product_data.txt", ios::app);

    if (outFile.is_open()) {
        outFile << productName << ","
                << productType << ","
                << productDescription << ","
                << costPrice << ","
                << sellingPrice << ","
                << expiryDate << "\n";
        outFile.close();
        cout << "\n[Success] Detailed product '" << productName << "' added and saved to 'product_data.txt' successfully!\n";
    } else {
        cout << "\n[Error] Unable to open product file for writing!\n";
    }
}

// --- Function to Update Product Details in File ---
void handleUpdateProduct() {
    string productName;
    string newType, newDesc, newExpiry;
    double newCostPrice, newSellingPrice;
    string currentDate = "2026-08-23"; // የአሁን ጊዜ ማመሳከሪያ

    cout << "\n--- Update Product (Detailed) ---\n";
    cout << "Enter Product Name to Update: ";
    cin >> productName;

    ifstream inFile("product_data.txt");
    ofstream outFile("temp_product.txt"); // አዲሱን መረጃ ለመያዝ ጊዜያዊ ፋይል

    bool found = false;
    string line;

    if (inFile.is_open() && outFile.is_open()) {
        while (getline(inFile, line)) {
            // መረጃው በ 6 ሰንሰለቶች (5 ኮማዎች) የተከፋፈለ መሆኑን ማረጋገጥ
            size_t p1 = line.find(',');
            size_t p2 = line.find(',', p1 + 1);
            size_t p3 = line.find(',', p2 + 1);
            size_t p4 = line.find(',', p3 + 1);
            size_t p5 = line.find(',', p4 + 1);

            if (p1 != string::npos && p2 != string::npos && p3 != string::npos && p4 != string::npos && p5 != string::npos) {
                string savedName = line.substr(0, p1);
                string savedType = line.substr(p1 + 1, p2 - p1 - 1);
                string savedDesc = line.substr(p2 + 1, p3 - p2 - 1);
                string savedCost = line.substr(p3 + 1, p4 - p3 - 1);
                string savedSell = line.substr(p4 + 1, p5 - p4 - 1);
                string savedExpiry = line.substr(p5 + 1);

                if (savedName == productName) {
                    found = true;
                    cout << "\n[Verified] Product found in database!\n";
                    cout << " - Current Type: " << savedType << "\n";
                    cout << " - Current Description: " << savedDesc << "\n";
                    cout << " - Current Cost Price: " << savedCost << "\n";
                    cout << " - Current Selling Price: " << savedSell << "\n";
                    cout << " - Current Expiry Date: " << savedExpiry << "\n\n";

                    // የኢንፑት ማህደረ ትውስታ (Buffer) ማጽዳት
                    cin.ignore();

                    cout << "Enter New Product Type: ";
                    getline(cin, newType);

                    cout << "Enter New Product Description: ";
                    getline(cin, newDesc);

                    // አዲስ የግዢ ዋጋ (Cost Price) ማረጋገጫ
                    while (true) {
                        cout << "Enter New Cost Price: ";
                        cin >> newCostPrice;
                        if (newCostPrice <= 0) {
                            cout << "\n[Error] Invalid Cost Price! Must be greater than 0. Try again.\n";
                        } else {
                            break;
                        }
                    }

                    // አዲስ የመሸጫ ዋጋ (Selling Price) ማረጋገጫ
                    while (true) {
                        cout << "Enter New Selling Price: ";
                        cin >> newSellingPrice;
                        if (newSellingPrice <= 0) {
                            cout << "\n[Error] Invalid Selling Price! Must be greater than 0. Try again.\n";
                        } else if (newSellingPrice < newCostPrice) {
                            cout << "\n[Warning] Selling price is less than cost price! Proceeding anyway...\n";
                            break;
                        } else {
                            break;
                        }
                    }

                    // አዲስ የማብቂያ ቀን (Expiry Date) ማረጋገጫ
                    while (true) {
                        cout << "Enter New Expiry Date (YYYY-MM-DD): ";
                        cin >> newExpiry;
                        if (newExpiry < currentDate) {
                            cout << "\n[Error] Invalid Expiry Date! Date is in the past. Try again.\n";
                        } else {
                            break;
                        }
                    }

// የተስተካከለው ሙሉ መረጃ ጊዜያዊ ፋይል ላይ በቅደም ተከተል ይጻፋል
                    outFile << savedName << ","
                            << newType << ","
                            << newDesc << ","
                            << newCostPrice << ","
                            << newSellingPrice << ","
                            << newExpiry << "\n";

                    cout << "\n[Success] Product '" << productName << "' updated successfully!\n";
                } else {
                    // ሌሎች ምርቶች ሳይለወጡ እንዳሉ ወደ ጊዜያዊው ፋይል ይገለበጣሉ
                    outFile << line << "\n";
                }
            } else {
                outFile << line << "\n";
            }
        }
        inFile.close();
        outFile.close();

        // ዋናውን ፋይል ሰርዘን በጊዜያዊው ፋይል እንተካዋለን
        remove("product_data.txt");
        rename("temp_product.txt", "product_data.txt");
    } else {
        cout << "\n[Error] Unable to open product data file!\n";
        return;
    }

    if (!found) {
        cout << "\n[Error] Product '" << productName << "' not found in database!\n";
        remove("temp_product.txt"); // ጊዜያዊ ፋይሉን እናጸዳለን
    }
}

// --- Function to Delete Product from File ---
void handleDeleteProduct() {
    string productName;

    cout << "\n--- Delete Product ---\n";
    cout << "Enter Product Name to Delete: ";
    cin >> productName;

    ifstream inFile("product_data.txt");
    ofstream outFile("temp_product.txt"); // ያልተሰረዙትን ምርቶች ለመያዝ ጊዜያዊ ፋይል

    bool found = false;
    string line;

    if (inFile.is_open() && outFile.is_open()) {
        while (getline(inFile, line)) {
            // የመጀመሪያውን ኮማ በመፈለግ የምርት ስሙን ብቻ መለየት
            size_t commaPos1 = line.find(',');

            if (commaPos1 != string::npos) {
                string savedName = line.substr(0, commaPos1);

                // ሊሰረዘው የገባው ስም ከፋይሉ ጋር የሚመሳሰል ከሆነ ጊዜያዊ ፋይል ላይ አይጻፍም (ይሰረዛል)
                if (savedName == productName) {
                    found = true;
                    cout << "\n[Success] Product '" << productName << "' has been deleted successfully!\n";
                } else {
                    // ሌሎቹ ምርቶች ሙሉ መረጃቸው እንዳሉ ወደ ጊዜያዊው ፋይል ይገለበጣሉ
                    outFile << line << "\n";
                }
            } else {
                // መስመሩ የተሳሳተ ቅርጸት ካለው እንዳይጠፋ እንዳለ ይገለበጣል
                outFile << line << "\n";
            }
        }
        inFile.close();
        outFile.close();

        // ዋናውን ፋይል ሰርዘን በጊዜያዊው ፋይል እንተካዋለን
        remove("product_data.txt");
        rename("temp_product.txt", "product_data.txt");
    } else {
        cout << "\n[Error] Unable to open product data file!\n";
        return;
    }

    if (!found) {
        cout << "\n[Error] Product '" << productName << "' not found in database!\n";
        remove("temp_product.txt"); // ጊዜያዊ ፋይሉን እናጸዳለን
    }
}

// --- Function to handle Add Stock ---
void handleAddStock() {
    string stockName;
    int quantity;
    string expiryDate;
    string currentDate = "2026-08-22"; // Current Date Context

    cout << "\n--- Add Stock (Validation & Expiry Analysis) ---\n";
    cout << "Enter Item Name: ";
    cin >> stockName;

    // Loop to ensure quantity is greater than 0 (No negative or zero allowed)
    while (true) {
        cout << "Enter Quantity: ";
        cin >> quantity;

        if (quantity <= 0) {
            cout << "\n[Error] Invalid Quantity! Quantity must be greater than 0. Please enter a valid amount.\n";
        } else {
            break;
        }
    }

    // Loop to ensure past/expired dates are rejected
    while (true) {
        cout << "Enter Expiry Date (YYYY-MM-DD): ";
        cin >> expiryDate;

        if (expiryDate < currentDate) {
            cout << "\n[Error] Invalid Expiry Date! This date is already in the past (Expired). You cannot add expired stock. Please try again.\n";
        } else {
            break;
        }
    }

    // Extracting Year, Month, and Day to calculate remaining days approximately
    int expYear = stoi(expiryDate.substr(0, 4));
    int expMonth = stoi(expiryDate.substr(5, 2));
    int expDay = stoi(expiryDate.substr(8, 2));

    int currYear = 2026, currMonth = 8, currDay = 22;
    int remainingDays = (expYear - currYear) * 365 + (expMonth - currMonth) * 30 + (expDay - currDay);

    // Success Message
    cout << "\n[Success] " << quantity << " units of '" << stockName
         << "' (Expires: " << expiryDate
         << ") added to stock successfully!\n";

    // Smart Expiry Recommendation System
    cout << "-----------------------------------------\n";
    cout << " [Smart Expiry Analysis & Recommendation]:\n";
    cout << " - Remaining Days to Expiry: Approximately " << remainingDays << " days\n";

if (remainingDays <= 30) {
        cout << " - Recommendation: URGENT! This stock is expiring soon (within 30 days). Recommend selling it quickly or putting it on discount/promotion!\n";
    } else if (remainingDays <= 90) {
        cout << " - Recommendation: Moderate shelf life. Monitor sales closely and apply FIFO (First-In, First-Out).\n";
    } else {
        cout << " - Recommendation: Good shelf life. Safe for regular storage and standard sales.\n";
    }
    cout << "-----------------------------------------\n";
}

// --- Function to handle Update Stock by Item Name (Reads from File) ---
void handleUpdateStock() {
    string stockName;
    int quantity;
    string expiryDate;
    string currentDate = "2026-08-22";

    cout << "\n--- Update Stock (Verification & Analysis) ---\n";
    cout << "Enter Item Name to Update: ";
    cin >> stockName;

    // ፋይሉን በመክፈት የተጻፈው እቃ መኖሩን በውስጡ መፈለግ
    ifstream inFile("stock_data.txt");
    bool found = false;
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            // መረጃው በ CSV (Name,Quantity,Expiry) መልክ ስለተቀመጠ ስሙን ብቻ እንለያለን
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string savedName = line.substr(0, commaPos);
                if (savedName == stockName) {
                    found = true;
                    break;
                }
            }
        }
        inFile.close();
    }

    // እቃው በፋይሉ ውስጥ ካልተገኘ
    if (!found) {
        cout << "\n[Error] Stock Not Found! No item named '" << stockName
             << "' exists in the system file. You cannot update a non-existent stock.\n";
        return;
    }

    cout << "\n[Verified] Stock found successfully in file! Proceeding to update...\n";

    // Loop to ensure updated quantity is greater than 0
    while (true) {
        cout << "Enter New Quantity: ";
        cin >> quantity;

        if (quantity <= 0) {
            cout << "\n[Error] Invalid Quantity! Quantity must be greater than 0. Please enter a valid amount.\n";
        } else {
            break;
        }
    }

    // Loop to ensure past/expired dates are rejected
    while (true) {
        cout << "Enter New Expiry Date (YYYY-MM-DD): ";
        cin >> expiryDate;

        if (expiryDate < currentDate) {
            cout << "\n[Error] Invalid Expiry Date! This date is already in the past (Expired). Please enter a valid future date.\n";
        } else {
            break;
        }
    }

    // Extracting Year, Month, and Day to calculate remaining days approximately
    int expYear = stoi(expiryDate.substr(0, 4));
    int expMonth = stoi(expiryDate.substr(5, 2));
    int expDay = stoi(expiryDate.substr(8, 2));

    int currYear = 2026, currMonth = 8, currDay = 22;
    int remainingDays = (expYear - currYear) * 365 + (expMonth - currMonth) * 30 + (expDay - currDay);

    // Success Message
    cout << "\n[Success] Stock for '" << stockName
         << "' has been updated successfully!\n"
         << " - New Quantity: " << quantity << "\n"
         << " - New Expiry Date: " << expiryDate << "\n";

    // Smart Expiry Recommendation System
    cout << "-----------------------------------------\n";
    cout << " [Smart Expiry Analysis & Recommendation]:\n";
    cout << " - Remaining Days to Expiry: Approximately " << remainingDays << " days\n";

    if (remainingDays <= 30) {
        cout << " - Recommendation: URGENT! This updated stock is expiring soon (within 30 days). Recommend selling it quickly or putting it on discount/promotion!\n";
    } else if (remainingDays <= 90) {
        cout << " - Recommendation: Moderate shelf life. Monitor sales closely and apply FIFO (First-In, First-Out).\n";
    } else {
        cout << " - Recommendation: Good shelf life. Safe for regular storage and standard sales.\n";
    }
    cout << "-----------------------------------------\n";
}

// --- Function to handle Delete Stock ---
void handleDeleteStock() {
    string stockName;

    cout << "\n--- Delete Stock ---\n";
    cout << "Enter Item Name to Delete: ";
    cin >> stockName;

    cout << "\n[Success] '" << stockName << "' has been deleted from stock successfully!\n";
}

// --- Function to View Reports from File/Database Structure ---
void handleViewReport() {
    ifstream inFile("report_data.txt");
    string line;
    int reportCount = 0;

    cout << "\n=========================================\n";
    cout << "          System Reports Management      \n";
    cout << "=========================================\n";
    cout << " 1. View All Reports (Report Table)\n";
    cout << " 2. View Report Content Only (Report_Content Table)\n";
    cout << "-----------------------------------------\n";

    int choice;
    cout << "Enter choice (1-2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "\n-----------------------------------------\n";
        cout << "          Report Table Records           \n";
        cout << "-----------------------------------------\n";

        if (inFile.is_open()) {
            if (inFile.peek() == ifstream::traits_type::eof()) {
                cout << " [Info] No reports found in the database yet!\n";
            } else {
                cout << "No. | Report Type    | Generation Date | Content Preview\n";
                cout << "---------------------------------------------------------\n";

                while (getline(inFile, line)) {
                    size_t p1 = line.find(',');
                    size_t p2 = line.find(',', p1 + 1);

                    if (p1 != string::npos && p2 != string::npos) {
                        string reportType = line.substr(0, p1);
                        string reportContent = line.substr(p1 + 1, p2 - p1 - 1);
                        string generationDate = line.substr(p2 + 1);

                        reportCount++;
                        cout << " " << reportCount << ".  | "
                             << reportType << "\t| "
                             << generationDate << "\t | "
                             << reportContent << "\n";
                    }
                }
            }
            inFile.close();
        } else {
            cout << " [Error] Could not open 'report_data.txt' file!\n";
        }
    }
    else if (choice == 2) {
        cout << "\n-----------------------------------------\n";
        cout << "       Report Content Only (Detailed)    \n";
        cout << "-----------------------------------------\n";

        if (inFile.is_open()) {
            if (inFile.peek() == ifstream::traits_type::eof()) {
                cout << " [Info] No content found!\n";
            } else {
                while (getline(inFile, line)) {
                    size_t p1 = line.find(',');
                    size_t p2 = line.find(',', p1 + 1);

                    if (p1 != string::npos && p2 != string::npos) {
                        string reportContent = line.substr(p1 + 1, p2 - p1 - 1);
                        reportCount++;
                        cout << " [" << reportCount << "] Content: " << reportContent << "\n";
                    }
                }
            }
            inFile.close();
        } else {
            cout << " [Error] Could not open file!\n";
        }
    }
    else {
        cout << "\n[Error] Invalid choice!\n";
    }
    cout << "=========================================\n";
}

// --- Function to View Low Stock Alerts from File ---
void handleViewLowStockAlert() {
    ifstream inFile("stock_data.txt");
    string line;
    int lowStockCount = 0;
    int threshold = 5; // የዝቅተኛ ስቶክ ገደብ (ከዚህ መጠን ካነሰ ማስጠንቀቂያ ይሰጣል)

    cout << "\n=========================================\n";
    cout << "           Low-Stock Alerts             \n";
    cout << "=========================================\n";

    if (inFile.is_open()) {
        // ፋይሉ ባዶ መሆኑን ማረጋገጥ
        if (inFile.peek() == ifstream::traits_type::eof()) {
            cout << " [Info] The stock is currently empty! No items found.\n";
        } else {
            cout << "No. | Item Name       | Quantity | Status\n";
            cout << "-----------------------------------------\n";

            while (getline(inFile, line)) {
                size_t commaPos1 = line.find(',');
                size_t commaPos2 = line.find(',', commaPos1 + 1);

                if (commaPos1 != string::npos && commaPos2 != string::npos) {
                    string stockName = line.substr(0, commaPos1);
                    int quantity = stoi(line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1));
                    string expiryDate = line.substr(commaPos2 + 1);

                    // መጠኑ ከወሰንነው ገደብ (Threshold) እኩል ወይም በታች ከሆነ
                    if (quantity <= threshold) {
                        lowStockCount++;
                        cout << " " << lowStockCount << ".  | "
                             << stockName << "\t\t| "
                             << quantity << "\t | [WARNING] Low Stock!\n";
                    }
                }
            }

            if (lowStockCount == 0) {
                cout << " [Info] Great! No low-stock items found. All items have sufficient quantity (above " << threshold << ").\n";
            }
        }
        inFile.close();
    } else {
        cout << " [Error] Could not open stock data file or file doesn't exist yet!\n";
    }
    cout << "=========================================\n";
}

// --- Function to View Expiry Alerts from File ---
void handleViewExpiryAlert() {
    ifstream inFile("stock_data.txt");
    string line;
    int expiryAlertCount = 0;
    string currentDate = "2026-08-23"; // የአሁን ጊዜ ማመሳከሪያ

    int currYear = 2026, currMonth = 8, currDay = 23;

    cout << "\n=========================================\n";
    cout << "           Expiry Date Alerts            \n";
    cout << "=========================================\n";

    if (inFile.is_open()) {
        if (inFile.peek() == ifstream::traits_type::eof()) {
            cout << " [Info] The stock is currently empty! No items found.\n";
        } else {
            cout << "No. | Item Name       | Expiry Date | Status / Remaining Days\n";
            cout << "-------------------------------------------------------------\n";

            while (getline(inFile, line)) {
                size_t commaPos1 = line.find(',');
                size_t commaPos2 = line.find(',', commaPos1 + 1);

                if (commaPos1 != string::npos && commaPos2 != string::npos) {
                    string stockName = line.substr(0, commaPos1);
                    string quantity = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
                    string expiryDate = line.substr(commaPos2 + 1);

                    // የቀኑን ርዝመት ማረጋገጥ (YYYY-MM-DD መሆኑን ለማረጋገጥ)
                    if (expiryDate.length() >= 10) {
                        int expYear = stoi(expiryDate.substr(0, 4));
                        int expMonth = stoi(expiryDate.substr(5, 2));
                        int expDay = stoi(expiryDate.substr(8, 2));

                        // የቀሩትን ቀናት በግምገማ ማስላት
                        int remainingDays = (expYear - currYear) * 365 + (expMonth - currMonth) * 30 + (expDay - currDay);

                        // ቀኑ ያለፈባቸው ወይም ከ 30 ቀናት በታች የቀራቸው እቃዎች ካሉ
                        if (remainingDays <= 30) {
                            expiryAlertCount++;
                            cout << " " << expiryAlertCount << ".  | "
                                 << stockName << "\t\t| "
                                 << expiryDate << " | ";

                            if (remainingDays < 0) {
                                cout << "[EXPIRED!] (" << -remainingDays << " days ago)\n";
                            } else if (remainingDays == 0) {
                                cout << "[EXPIRES TODAY!]\n";
                            } else {
                                cout << "[URGENT] " << remainingDays << " days left\n";
                            }
                        }
                    }
                }
            }

            if (expiryAlertCount == 0) {
                cout << " [Info] Great! No expiring items found. All items have safe shelf life (> 30 days).\n";
            }
        }
        inFile.close();
    } else {
        cout << " [Error] Could not open stock data file or file doesn't exist yet!\n";
    }
    cout << "=========================================\n";
}

// --- Function to Generate Report and Save to Both Tables/Files ---
void handleGenerateReport() {
    string reportType, reportContent;
    string generationDate = "2026-08-23"; // ወቅታዊው ቀን

    cout << "\n--- Generate New Report ---\n";

    // ከዚህ በፊት የነበረውን የኢንፑት ማህደረ ትውስታ (Buffer) ማጽዳት
    cin.ignore();

    cout << "Enter Report Type (e.g., Sales Summary, Low Stock, Expiry): ";
    getline(cin, reportType);

    cout << "Enter Report Content / Details: ";
    getline(cin, reportContent);

    // 1. መረጃውን ለ 'Report' ሰንጠረዥ (Report Type, Content, Date) በፋይል ማስቀመጥ
    ofstream reportFile("report_data.txt", ios::app);

    // 2. መረጃውን ለ 'Report_Content' ሰንጠረዥ (Content ብቻ) በሌላ ፋይል ማስቀመጥ
    ofstream contentFile("report_content_data.txt", ios::app);

    if (reportFile.is_open() && contentFile.is_open()) {
        // Report table ላይ መጻፍ
        reportFile << reportType << "," << reportContent << "," << generationDate << "\n";

        // Report_Content table ላይ መጻፍ
        contentFile << reportContent << "\n";

        reportFile.close();
        contentFile.close();

        cout << "\n[Success] Report generated successfully and saved to both 'Report' and 'Report_Content' databases!\n";
        cout << " - Date Generated: " << generationDate << "\n";
    } else {
        cout << "\n[Error] Unable to open report database files for writing!\n";
    }
}

// --- Function to Check Income, Cost, and Potential Profit ---
void handleCheckIncomeAndCost() {
    ifstream stockFile("stock_data.txt");

    double totalCost = 0.0;
    double totalPotentialIncome = 0.0;
    int itemCount = 0;

    cout << "\n=========================================\n";
    cout << "         Financial Summary (Income & Cost) \n";
    cout << "=========================================\n";

    if (!stockFile.is_open()) {
        cout << " [Error] Could not open stock data file!\n";
        return;
    }

    string stockLine;
    while (getline(stockFile, stockLine)) {
        size_t s1 = stockLine.find(',');
        size_t s2 = stockLine.find(',', s1 + 1);

        if (s1 != string::npos && s2 != string::npos) {
            string stockName = stockLine.substr(0, s1);
            int quantity = stoi(stockLine.substr(s1 + 1, s2 - s1 - 1));

            // የዋጋ ዝርዝሮችን ለማግኘት product_data.txt ፋይልን መክፈት
            ifstream productFile("product_data.txt");
            string productLine;
            bool productFound = false;

            if (productFile.is_open()) {
                while (getline(productFile, productLine)) {
                    size_t p1 = productLine.find(',');
                    size_t p2 = productLine.find(',', p1 + 1);
                    size_t p3 = productLine.find(',', p2 + 1);
                    size_t p4 = productLine.find(',', p3 + 1);
                    size_t p5 = productLine.find(',', p4 + 1);

                    if (p1 != string::npos && p5 != string::npos) {
                        string pName = productLine.substr(0, p1);
                        if (pName == stockName) {
                            // Cost Price እና Selling Price ከፋይሉ ማንበብ
                            double costPrice = stod(productLine.substr(p3 + 1, p4 - p3 - 1));
                            double sellingPrice = stod(productLine.substr(p4 + 1, p5 - p4 - 1));

                            double itemCost = costPrice * quantity;
                            double itemIncome = sellingPrice * quantity;

                            totalCost += itemCost;
                            totalPotentialIncome += itemIncome;
                            itemCount++;

                            cout << " Item: " << stockName << " (Qty: " << quantity << ")\n";
                            cout << "   - Cost: " << itemCost << " ETB | Potential Revenue: " << itemIncome << " ETB\n";
                            cout << "-----------------------------------------\n";
                            productFound = true;
                            break;
                        }
                    }
                }
                productFile.close();
            }
        }
    }
    stockFile.close();

    if (itemCount == 0) {
        cout << " [Info] No stock records or matching product prices found to calculate.\n";
    } else {
        double totalProfit = totalPotentialIncome - totalCost;
        cout << "\n=========================================\n";
        cout << "          OVERALL FINANCIAL REPORT       \n";
        cout << "=========================================\n";
        cout << " Total Inventory Cost (Investment): " << totalCost << " ETB\n";
        cout << " Total Potential Income (Revenue):  " << totalPotentialIncome << " ETB\n";
        cout << " Estimated Net Profit:              " << totalProfit << " ETB\n";
        cout << "=========================================\n";
    }
}



// --- Owner Dashboard ---
void handleOwnerDashboard(bool &isLoggedIn) {
    int choice;
    do {
        cout << "\n=========================================\n";
        cout << "       Owner Main Dashboard              \n";
        cout << "=========================================\n";
        cout << " 1. Record Sales\n";
        cout << " 2. View Stock\n";
        cout << " 3. Manage Product (Add, Update, Delete)\n";
        cout << " 4. Manage Stock (Add, Update, Delete)\n";
        cout << " 5. View Reports\n";
        cout << " 6. View Low-Stock Alert\n";
        cout << " 7. View Expiry Alert\n";
        cout << " 8. Generate Report\n";
        cout << " 9. Check Income and Cost\n";
        cout << "10. Logout\n";
        cout << "-----------------------------------------\n";
        cout << "Enter your choice (1-10): ";
        cin >> choice;

        switch (choice) {
            case 1:
                handleRecordSales();
                break;
            case 2:
                handleViewStock();
                break;
            case 3: {
                int productChoice;
                cout << "\n--- Manage Product ---\n";
                cout << "1. Add Product\n";
                cout << "2. Update Product\n";
                cout << "3. Delete Product\n";
                cout << "Enter choice (1-3): ";
                cin >> productChoice;
                if (productChoice == 1) {
                    handleAddProduct();
                } else if (productChoice == 2) {
                    handleUpdateProduct();
                } else if (productChoice == 3) {
                    handleDeleteProduct();
                } else {
                    cout << "\n[Error] Invalid choice!\n";
                }
                break;
            }
            case 4: {
                int stockChoice;
                cout << "\n--- Manage Stock ---\n";
                cout << "1. Add Stock (with File Storage)\n";
                cout << "2. Update Stock\n";
                cout << "3. Delete Stock\n";
                cout << "Enter choice (1-3): ";
                cin >> stockChoice;
                if (stockChoice == 1) {
                    handleAddStockToFile();
                } else if (stockChoice == 2) {
                    handleUpdateStock();
                } else if (stockChoice == 3) {
                    handleDeleteStock();
                } else {
                    cout << "\n[Info] Operation completed.\n";
                }
                break;
            }
            case 5:
                handleViewReport();
                break;
            case 6:
                handleViewLowStockAlert();
                break;
            case 7:
                handleViewExpiryAlert();
                break;
            case 8:
                handleGenerateReport();
                break;
            case 9:
                handleCheckIncomeAndCost();
                break;
            case 10:
                cout << "\n[Success] Logged out from Owner account successfully.\n";
                isLoggedIn = false;
                break;
            default:
                cout << "\n[Error] Invalid choice! Please enter a number between 1 and 10.\n";
        }
    } while (isLoggedIn);
}

// --- Accountant Dashboard ---
void handleAccountantDashboard(bool &isLoggedIn) {
    int choice;
    do {
        cout << "\n=========================================\n";
        cout << "       Accountant Dashboard              \n";
        cout << "=========================================\n";
        cout << " 1. View Report\n";
        cout << " 2. Logout\n";
        cout << "-----------------------------------------\n";
        cout << "Enter choice (1-2): ";
        cin >> choice;

        if (choice == 1) {
            handleViewReport();

} else if (choice == 2) {
            cout << "\n[Success] Logged out from Accountant account successfully.\n";
            isLoggedIn = false;
        } else {
            cout << "\n[Error] Invalid choice! Please select a valid option.\n";
        }
    } while (isLoggedIn);
}

// --- Authentication Function ---
bool authenticateUser(string role, string correctUser, string correctPass) {
    string username, password;

    cout << "\n--- " << role << " Login ---\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    bool hasUppercase = false;
    for (char c : username) {
        if (isupper(c)) {
            hasUppercase = true;
            break;
        }
    }
    for (char c : password) {
        if (isupper(c)) {
            hasUppercase = true;
            break;
        }
    }

    if (hasUppercase) {
        cout << "\n[Error] Please use lowercase letters for username and password.\n";
        return false; // ሎጊን አልተሳካም (Capital ፊደል ስላለ)
    }

    if (username == correctUser && password == correctPass) {
        cout << "\n[Success] " << role << " Login Successful!\n";

        // የኢንፑት ማህደረ ትውስታውን በንጽህና ማጽዳት
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        return true; // ሎጊኑ በሰላም ተሳክቷል!
    } else {
        cout << "\n[Error] Incorrect username or password!\n";
        return false;
    }
}

// --- External Payment System ---
bool authenticateExternalPaymentSystem() {
    string apiKey;
    string validApiKey = "EXT_PAY_API_2026";
    int choice;
    bool isConnected = true;
    int maxAttempts = 3;

    for (int attempt = 1; attempt <= maxAttempts; attempt++) {
        cout << "\n--- External Payment Integration (Attempt " << attempt << "/" << maxAttempts << ") ---\n";
        cout << "Enter API Token Key: ";
        cin >> apiKey;

        if (apiKey == validApiKey) {
            cout << "\n[Success] Payment Integration connected successfully!\n";

            do {
                cout << "\n-----------------------------------------\n";
                cout << "    Payment Dashboard\n";
                cout << "-----------------------------------------\n";
                cout << " 1. Payment Integration\n";
                cout << " 2. Logout / Disconnect\n";
                cout << "-----------------------------------------\n";
                cout << "Enter choice (1-2): ";
                cin >> choice;

                if (choice == 1) {
                    handlePaymentIntegration();
                } else if (choice == 2) {
                    cout << "\n[Success] Disconnected from External Payment System.\n";
                    isConnected = false;
                } else {
                    cout << "\n[Error] Invalid choice! Please select a valid option.\n";
                }
            } while (isConnected);

            return true;
        } else {
            cout << "\n[Error] Invalid API Token Key!\n";
        }
    }

    cout << "\n[Warning] 3 failed attempts! Returning to main menu.\n";
    return false;
}

// --- Help Menu ---
void handleHelpMenu() {
    int helpChoice;
    do {
        cout << "\n=========================================\n";
        cout << "       Help & System Guide Menu          \n";
        cout << "=========================================\n";
        cout << " 1. System Overview & Instructions\n";
        cout << " 2. Admin Support (Resolve Username/Password Issues)\n";
        cout << " 3. Back to Main Menu\n";
        cout << "-----------------------------------------\n";
        cout << "Enter choice (1-3): ";
        cin >> helpChoice;

        if (helpChoice == 1) {
            cout << "\n-----------------------------------------\n";
            cout << " [System Guide & Overview]:\n";
            cout << " - Owner Login: Manages sales, stock, products, and reports.\n";
            cout << " - Accountant Login: Views financial reports and tables.\n";
            cout << " - External Payment System: Handles online API transactions.\n";
            cout << " - Security Feature: You get up to 3 attempts during login.\n";
            cout << "-----------------------------------------\n";
        } else if (helpChoice == 2) {
            string adminUser, adminPass;
            int maxAttempts = 3;
            bool adminVerified = false;

            for (int attempt = 1; attempt <= maxAttempts; attempt++) {
                cout << "\n--- Admin Help Desk Login (Attempt " << attempt << "/" << maxAttempts << ") ---\n";
                cout << "Enter Admin Username: ";
                cin >> adminUser;
                cout << "Enter Admin Password: ";
                cin >> adminPass;

                if (adminUser == "admin123" && adminPass == "pass123") {

cout << "\n[Success] Admin Authenticated Successfully!\n";
                    cout << "-----------------------------------------\n";
                    cout << " [Default Credentials Lookup]:\n";
                    cout << " - Owner Username: owner123 | Password: pass123\n";
                    cout << " - Accountant Username: accountant123 | Password: pass123\n";
                    cout << "-----------------------------------------\n";
                    adminVerified = true;
                    break;
                } else {
                    cout << "\n[Error] Incorrect Admin credentials!\n";
                }
            }
            if (!adminVerified) {
                cout << "\n[Warning] Admin verification failed after 3 attempts.\n";
            }
        } else if (helpChoice == 3) {
            cout << "\nReturning to Main Menu...\n";
        } else {
            cout << "\n[Error] Invalid choice! Please select between 1 and 3.\n";
        }
    } while (helpChoice != 3);
}

// --- Main Function ---
int main() {
    int choice;

    do {
        cout << "\n=========================================\n";
        cout << "       System Main Menu                 \n";
        cout << "=========================================\n";
        cout << " 1. Owner Login\n";
        cout << " 2. Accountant Login\n";
        cout << " 3. External Payment System\n";
        cout << " 4. Help & System Guide\n";
        cout << " 5. Exit\n";
        cout << "-----------------------------------------\n";
        cout << "Enter choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // ሎጊኑ ትክክል ከሆነ ብቻ የ Owner ዳሽቦርድን ይክፈት
                if (authenticateUser("Owner", "owner123", "pass123")) {
                    bool isLoggedIn = true;
                    handleOwnerDashboard(isLoggedIn);
                }
                break;
            }
            case 2: {
                // ሎጊኑ ትክክል ከሆነ ብቻ የ Accountant ዳሽቦርድን ይክፈት
                if (authenticateUser("Accountant", "accountant123", "pass123")) {
                    bool isLoggedIn = true;
                    handleAccountantDashboard(isLoggedIn);
                }
                break;
            }
            case 3:
                authenticateExternalPaymentSystem();
                break;
            case 4:
                handleHelpMenu();
                break;
            case 5:
                cout << "\nExiting program... Goodbye!\n";
                break;
            default:
                cout << "\n[Error] Invalid choice! Please enter a number between 1 and 5.\n";
        }

    } while (choice != 5);

    return 0;
}
