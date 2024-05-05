#include <string>
#include <deepstate/DeepState.hpp>
#include "OnlineStore.cpp"
using namespace deepstate;

std::string generateRandomString(int length) {
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += DeepState_Char();
    }
    return result;
}

// Define the generateRandomString function here

// Product class test cases
TEST(Product, AddToStore) {
  int stock = DeepState_IntInRange(1, 100);
  double price = DeepState_DoubleInRange(1.0, 1000.0);
  double discount = DeepState_DoubleInRange(0.0, 0.5); // Discount range: 0% to 50%
  std::string name = generateRandomString(5);

  Product product(name, price, stock, discount);
  OnlineStore store;
  store.addProduct(product);

  ASSERT_TRUE(store.hasProduct(name));
}

TEST(Product, ApplyDiscount) {
  int stock = DeepState_IntInRange(1, 100);
  double price = DeepState_DoubleInRange(1.0, 1000.0);
  double discount = DeepState_DoubleInRange(0.0, 0.5); // Discount range: 0% to 50%
  double newDiscount = DeepState_DoubleInRange(0.0, 0.5); // New discount range
  std::string name = generateRandomString(5);

  Product product(name, price, stock, discount);
  product.applyDiscount(newDiscount);

  ASSERT_EQ(product.getPrice(), price * (1.0 - newDiscount));
}

// Customer class test cases
TEST(Customer, AddToCartAndWishlist) {
  std::string name = generateRandomString(5);
  double balance = DeepState_DoubleInRange(0.0, 10000.0);
  Customer customer(name, balance);

  std::string productName = generateRandomString(5);
  Product product(productName, 100.0, 10);

  customer.addToCart(product);
  customer.addToWishlist(product);

  ASSERT_TRUE(customer.getCart().size() == 1);
  ASSERT_TRUE(customer.getWishlist().size() == 1);
}

TEST(Customer, RemoveFromCartAndWishlist) {
  std::string name = generateRandomString(5);
  double balance = DeepState_DoubleInRange(0.0, 10000.0);
  Customer customer(name, balance);

  std::string productName = generateRandomString(5);
  Product product(productName, 100.0, 10);

  customer.addToCart(product);
  customer.addToWishlist(product);

  customer.removeFromCart(productName);
  customer.removeFromWishlist(productName);

  ASSERT_TRUE(customer.getCart().empty());
  ASSERT_TRUE(customer.getWishlist().empty());
}

// OnlineStore class test cases
TEST(OnlineStore, PurchaseProduct) {
  std::string customerName = generateRandomString(5);
  double balance = DeepState_DoubleInRange(0.0, 10000.0);
  Customer customer(customerName, balance);

  std::string productName = generateRandomString(5);
  Product product(productName, 100.0, 10);

  OnlineStore store;
  store.addProduct(product);

  store.purchaseProduct(customer, productName);

  ASSERT_FALSE(customer.getCart().empty());
}

TEST(OnlineStore, AddAndFindCustomer) {
  std::string name = generateRandomString(5);
  double balance = DeepState_DoubleInRange(0.0, 10000.0);
  Customer customer(name, balance);

  OnlineStore store;
  store.addCustomer(&customer);

  ASSERT_TRUE(store.findCustomer(name) != nullptr);
}

// Admin class test cases
TEST(Admin, AddProductToStore) {
  std::string productName = generateRandomString(5);
  double price = DeepState_DoubleInRange(1.0, 1000.0);
  int stock = DeepState_IntInRange(1, 100);

  OnlineStore store;
  Admin::addProductToStore(store, productName, price, stock);

  ASSERT_TRUE(store.hasProduct(productName));
}

TEST(Admin, RemoveProductFromStore) {
  std::string productName = generateRandomString(5);
  double price = DeepState_DoubleInRange(1.0, 1000.0);
  int stock = DeepState_IntInRange(1, 100);

  OnlineStore store;
  Admin::addProductToStore(store, productName, price, stock);
  Admin::removeProductFromStore(store, productName);

  ASSERT_FALSE(store.hasProduct(productName));
}
