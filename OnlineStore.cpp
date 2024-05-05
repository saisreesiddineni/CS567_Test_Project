#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

// Forward declarations
class Product;
class Customer;
class PaymentMethod;
class OnlineStore;
class Admin;

// Payment method interface
class PaymentMethod {
public:
    virtual bool pay(double amount) = 0;
    virtual ~PaymentMethod() {}
};

// Cash payment method
class Cash : public PaymentMethod {
public:
    bool pay(double amount) override {
        return true;
    }
};

// Credit card payment method
class CreditCard : public PaymentMethod {
public:
    bool pay(double amount) override {
        return true;
    }
};

// Paypal payment method
class Paypal : public PaymentMethod {
public:
    bool pay(double amount) override {
        return true;
    }
};

// Review structure
struct Review {
    string customerName;
    string productName;
    string comment;
    int rating; // 1 to 5 stars
};

// Order structure
struct Order {
    string productName;
    double totalPrice;
    string status;
};

// Product class
class Product {
private:
    string name;
    double price;
    double discount;
    int stock;
public:
    Product(const string& _name, double _price, int _stock, double _discount = 5.0) : name(_name), price(_price), stock(_stock), discount(_discount) {}

    const string& getName() const {
        return name;
    }

    double getPrice() const {
        return price * (1.0 - discount);
    }

    int getStock() const {
        return stock;
    }

    void applyDiscount(double amount) {
        discount = min(discount + amount, 1.0); // Ensure discount doesn't exceed 100%
    }

    void decreaseStock() {
        if (stock > 0) {
            stock--;
        }
    }
};

// Customer class
class Customer {
private:
    string name;
    double balance;
    vector<Product> cart;
    vector<Product> wishlist;
    vector<Review> reviews;
    vector<Order> orders;
    PaymentMethod* paymentMethod;
    int loyaltyPoints;
public:
    Customer(const string& _name, double _balance) : name(_name), balance(_balance), paymentMethod(nullptr), loyaltyPoints(0) {}

    void addToCart(const Product& product) {
        cart.push_back(product);
    }

    void removeFromCart(const string& productName) {
        auto it = find_if(cart.begin(), cart.end(), [&productName](const Product& p) {
            return p.getName() == productName;
        });
        if (it != cart.end()) {
            cart.erase(it);
        }
    }

    void addToWishlist(const Product& product) {
        wishlist.push_back(product);
    }

    void removeFromWishlist(const string& productName) {
        auto it = find_if(wishlist.begin(), wishlist.end(), [&productName](const Product& p) {
            return p.getName() == productName;
        });
        if (it != wishlist.end()) {
            wishlist.erase(it);
        }
    }

    const vector<Product>& getCart() const {
        return cart;
    }

    const vector<Product>& getWishlist() const {
        return wishlist;
    }

    void displayCart() const {
        for (const auto& product : cart) {
            cout << product.getName() << " - $" << product.getPrice() << endl;
        }
    }

    void displayWishlist() const {
        cout << "Wishlist for " << name << ":" << endl;
        for (const auto& product : wishlist) {
            cout << product.getName() << " - $" << product.getPrice() << endl;
        }
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& product : cart) {
            total += product.getPrice();
        }
        return total;
    }

    bool checkout() {
        double total = calculateTotal();
        if (balance >= total && paymentMethod != nullptr) {
            if (paymentMethod->pay(total)) {
                balance -= total;
                // Increase loyalty points
                loyaltyPoints += 10;
                // Add order
                orders.push_back({cart[0].getName(), total, "Processing"});
                cart.clear();
                return true;
            }
        }
        return false;
    }

    void setPaymentMethod(PaymentMethod* method) {
        paymentMethod = method;
    }

    void addFunds(double amount) {
        balance += amount;
    }

    double getBalance() const {
        return balance;
    }

    void addReview(const Review& review) {
        reviews.push_back(review);
    }

    void viewReviews() const {
        for (const auto& review : reviews) {
            cout << "Product: " << review.productName << ", Rating: " << review.rating << " stars, Comment: " << review.comment << endl;
        }
    }

    void trackOrders() const {
        for (const auto& order : orders) {
            cout << "Product: " << order.productName << ", Total Price: $" << fixed << setprecision(2) << order.totalPrice << ", Status: " << order.status << endl;
        }
    }

    int getLoyaltyPoints() const {
        return loyaltyPoints;
    }

    const string& getName() const {
        return name;
    }
};

// Online store class
class OnlineStore {
private:
    vector<Product> products;
    map<string, Customer*> customers;
    friend class Admin; // Allowing Admin class to access private members of OnlineStore
public:
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    void displayProducts() const {
        cout << "Available Products:" << endl;
        for (const auto& product : products) {
            cout << product.getName() << " - $" << product.getPrice() << " - Stock: " << product.getStock() << endl;
        }
    }

    bool hasProduct(const std::string& productName) const {
    try {
        // Iterate through the products vector and check if the given product name exists
        for (const auto& product : products) {
            if (product.getName() == productName) {
                return true;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred in hasProduct: " << e.what() << std::endl;
        // Handle the exception gracefully, such as logging or returning a default value
    }
    // If the product name is not found or an exception occurs, return false
    return false;
}



    bool purchaseProduct(Customer& customer, const string& productName) {
        auto it = find_if(products.begin(), products.end(), [&productName](const Product& p) {
            return p.getName() == productName;
        });
        if (it != products.end()) {
            if (it->getStock() > 0) {
                customer.addToCart(*it);
                it->decreaseStock();
                return true;
            } else {
                cout << "Product '" << productName << "' is out of stock!" << endl;
            }
        }
        return false;
    }

    void addCustomer(Customer* customer) {
        customers[customer->getName()] = customer;
    }

    void displayCustomers() const {
        cout << "Registered Customers:" << endl;
        for (const auto& pair : customers) {
            cout << "- " << pair.first << endl;
        }
    }

    Customer* findCustomer(const string& name) {
        auto it = customers.find(name);
        if (it != customers.end()) {
            return it->second;
        }
        return nullptr;
    }
};



// Admin class
class Admin {
public:
    static void addProductToStore(OnlineStore& store, const string& productName, double price, int stock) {
        store.addProduct(Product(productName, price, stock));
    }

    static void addFundsToCustomer(OnlineStore& store, const string& customerName, double amount) {
        Customer* customer = store.findCustomer(customerName);
        if (customer) {
            customer->addFunds(amount);
        } else {
            cout << "Customer '" << customerName << "' not found!" << endl;
        }
    }

    static void removeProductFromStore(OnlineStore& store, const string& productName) {
        auto it = find_if(store.products.begin(), store.products.end(), [&productName](const Product& p) {
            return p.getName() == productName;
        });
        if (it != store.products.end()) {
            store.products.erase(it);
        } else {
            cout << "Product '" << productName << "' not found in the store!" << endl;
        }
    }

    static void applyDiscountToProduct(OnlineStore& store, const string& productName, double discountAmount) {
        auto it = find_if(store.products.begin(), store.products.end(), [&productName](const Product& p) {
            return p.getName() == productName;
        });
        if (it != store.products.end()) {
            it->applyDiscount(discountAmount);
            cout << "Discount applied to product '" << productName << "'!" << endl;
        } else {
            cout << "Product '" << productName << "' not found in the store!" << endl;
        }
    }

    static void viewSalesReport(const OnlineStore& store) {
        cout << "Sales Report:" << endl;
        // Add sales report generation logic here
    }

    static void manageInventory(OnlineStore& store) {
        // Add inventory management interface here
    }

    static void contactCustomerSupport(Customer& customer) {
        // Add customer support contact interface here
    }
};

