#include <iostream>
#include <string>
#include <vector>        

using namespace std;

namespace ariel {

    class Node {
        
        public:
            string _name;
            std::vector<Node*> _sub;
            Node(const string &name) { // constructor
                this->_name = name;
            }

            string get_name() const{
                return this->_name;
            }

            void set_name(const string &name) {
                this->_name = name;
            }
        
            std::vector<Node*> get_sub() const{
                return this->_sub;
            }

            Node& add_sub_to_node(Node* node) {
                this->_sub.push_back(node);
                return *this;
            }

            friend ostream &operator<<(ostream &os, Node *node) {
                os << node->_name;
                return os;
            }

    };
}