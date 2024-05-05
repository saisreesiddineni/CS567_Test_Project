#include "OnlineStore.cpp"
int main() {
    // Creating an online store
    OnlineStore store;

    // Adding products to the store
    Admin::addProductToStore(store, "Laptop", 999.99, 10);
    Admin::addProductToStore(store, "Smartphone", 599.99, 15);
    Admin::addProductToStore(store, "Headphones", 99.99, 20);

    // Displaying available products
    store.displayProducts();

    // Creating customers and setting their balance
    Customer customer1("Alice", 1500.0);
    Customer customer2("Bob", 2000.0);

    // Adding customers to the store
    store.addCustomer(&customer1);
    store.addCustomer(&customer2);

    // Customer 1 adding products to cart
    store.purchaseProduct(customer1, "Laptop");
    store.purchaseProduct(customer1, "Smartphone");

    // Customer 2 adding products to cart
    store.purchaseProduct(customer2, "Headphones");

    // Displaying customers' shopping carts and totals
    customer1.displayCart();
    cout << "Total for " << customer1.getName() << ": $" << fixed << setprecision(2) << customer1.calculateTotal() << endl;

    customer2.displayCart();
    cout << "Total for " << customer2.getName() << ": $" << fixed << setprecision(2) << customer2.calculateTotal() << endl;

    // Setting payment methods
    Cash cashMethod;
    CreditCard cardMethod;
    Paypal paypalMethod;

    customer1.setPaymentMethod(&cashMethod);
    customer2.setPaymentMethod(&paypalMethod);

    // Customers checkout
    customer1.checkout();
    customer2.checkout();

    // Adding funds to customer's account
    Admin::addFundsToCustomer(store, "Alice", 500.0);

    // Displaying customer's balance
    cout << "Balance for " << customer1.getName() << ": $" << fixed << setprecision(2) << customer1.getBalance() << endl;

    // Adding a review by customer1
    Review review1 = {"Alice", "Laptop", "Great laptop, highly recommended!", 5};
    customer1.addReview(review1);

    // Displaying reviews by customer1
    customer1.viewReviews();

    // Applying discount to a product
    Admin::applyDiscountToProduct(store, "Smartphone", 0.1); // 10% discount

    // Displaying available products after discount
    store.displayProducts();

    return 0;
}
