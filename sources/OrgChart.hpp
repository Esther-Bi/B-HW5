#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Node.hpp"

#ifndef MY_HEADER
#define MY_HEADER

namespace ariel {

    static const int LEVEL_ORDER = 0 ;
    static const int REVERSE_LEVEL_ORDER = 1 ;
    static const int PRE_ORDER = 2 ;

    class OrgChart{

        private:
            Node* root; 
                
        public:
            OrgChart(const OrgChart&) = default; // copy constructor
            OrgChart(OrgChart&&) = default; // move constructor
            OrgChart();
            ~OrgChart();   
            OrgChart &operator=(OrgChart const &other) = default; // copy operator
            OrgChart &operator=(OrgChart &&other) = default; // move operator (r value->new object)
            friend ostream& operator<<(ostream& os, const OrgChart &orgChart);
            OrgChart& add_root(const std::string &name);
            OrgChart& add_sub(const std::string& super_name, const std::string& sub_name);
            bool find_super(Node* root, const std::string& super, const std::string& sub);
            void delete_OrgChart(Node *root);

        
        class Iterator{
            
            private:
                Node* curr_node;
                vector<Node*> iterator_list;
            
            public:
                Iterator(int order, Node *p = nullptr) {
                    if (p != nullptr) {
                        switch (order) { // build iterators
                            case LEVEL_ORDER:
                                level_builder(p);
                                break;
                            case REVERSE_LEVEL_ORDER:
                                reverse_builder(p);
                                break;
                            case PRE_ORDER:
                                preorder_builder(p);
                                break;
                        }
                        this->curr_node = iterator_list.at(0); // remember first and delete it
                        iterator_list.erase(iterator_list.begin());
                    } else {
                        this->curr_node = nullptr; // return null if there isn't a orgchart
                    }
                }

                void level_builder(Node* root);
                void reverse_builder(Node* root);
                void preorder_builder(Node* root);

                bool operator!=(const Iterator& iterator) {
                    return this->curr_node != iterator.curr_node; // check if same
                }

                bool operator==(const Iterator& iterator) {
                    return this->curr_node == iterator.curr_node; // check if same
                }

                string operator*() {
                    return (*this->curr_node).get_name(); 
                }

                Iterator operator++(int) {
                    Iterator temp = *this; // save before changing
                    if (!iterator_list.empty()) {
                        this->curr_node = iterator_list.at(0); // take first and delete it
                        iterator_list.erase(iterator_list.begin());
                    }
                    else {
                        this->curr_node = nullptr;
                    }
                    return temp; // return before changing
                }

                Iterator& operator++() {
                    if (!iterator_list.empty()) {
                        this->curr_node = iterator_list.at(0); // take first and delete it
                        iterator_list.erase(iterator_list.begin());
                    }
                    else {
                        this->curr_node = nullptr;
                    }
                    return *this; // return after changing         
                }

                string* operator->() { // pointer
                    return &curr_node->_name; // return name of node
                }

            };

            Iterator begin_level_order();
            Iterator end_level_order();
            Iterator begin_reverse_order();
            Iterator reverse_order();
            Iterator begin_preorder();
            Iterator end_preorder();
            Iterator begin();
            Iterator end();
    };
   
}

#endif