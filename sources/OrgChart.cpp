#include "OrgChart.hpp"

namespace ariel{

    OrgChart::OrgChart() { // constructor
        this->root = nullptr;
    }

    OrgChart::~OrgChart() { // destuctor
        (*this).delete_OrgChart(this->root);
    }
    
    OrgChart& OrgChart::add_root(const string &name) {
        if (name.empty()) {
            throw invalid_argument("illegal string");
        }
        if(this->root != nullptr) { // change root's name
            (*this->root).set_name(name);
        } else {
            this->root = new Node(name); // build new node for root
        }
        return *this;
    }

    OrgChart& OrgChart::add_sub(const string& super_name, const string& sub_name) {
        if (super_name.empty() || sub_name.empty()) {
            throw invalid_argument("illegal string");
        }
        if (this->root == nullptr) {
            throw invalid_argument("there is no root");
        }
        if(!find_super(this->root, super_name, sub_name)) { // search for super and add to his sub vector if finds
            throw invalid_argument("super doesn't exist");
        }
        return *this;
    }

    bool OrgChart::find_super(Node* root, const string& super, const string& sub) {
        if((*root).get_name()==super){
            Node* new_sub = new Node(sub);
            (*root).add_sub_to_node(new_sub); // add a child and end
            return true;
        }
        for (size_t i=0; i<(*root).get_sub().size(); i++) {
            if (find_super((*root).get_sub().at(i), super, sub)){ // recursive
                return true;
            }
        }
        return false;
    }

    ostream& operator<<(ostream& os, const OrgChart &orgChart) {
        std::list<Node*> p;
        if((orgChart.root == NULL)){
            throw std::runtime_error("orgChart is empty");
        }
        p.push_back(orgChart.root);
        while(!(p.empty())){
            for (size_t i=0; i<p.size(); i++){
                Node* tmp = p.front();
                p.pop_front();
                os << (*tmp).get_name() << " ";
                if (!((*tmp).get_sub().empty())){
                    for (size_t i=0; i<(*tmp).get_sub().size(); i++){
                        p.push_back((*tmp).get_sub().at(i));
                    }
                }
            }
            os << std::endl;
        }
        return os;
    }

    void OrgChart::Iterator::level_builder(Node* root) {
        vector<Node*> temp_vec_for_fill; // push and pop for good order
        temp_vec_for_fill.push_back(root); // init with root
        while(!temp_vec_for_fill.empty()){ // use tenp untill empty
            Node* curr_node =  temp_vec_for_fill[0]; // take first to iterator
            this->iterator_list.push_back(curr_node); 
            for(unsigned long j=0; j<(*curr_node).get_sub().size(); j++){ // add all children to temp for level order
                temp_vec_for_fill.push_back((*curr_node).get_sub().at(j));
            }
            temp_vec_for_fill.erase(temp_vec_for_fill.begin()); // delete first from tenp, already in iterator
        }  
    }

    OrgChart::Iterator OrgChart::begin_level_order() {
        if (this->root == nullptr) {
            throw invalid_argument("orgChart is empty");
        }
        return Iterator{LEVEL_ORDER, root};    
    }

    OrgChart::Iterator OrgChart::end_level_order() {
        if (this->root == nullptr) {
            throw invalid_argument("orgChart is empty");
        }
        return Iterator{LEVEL_ORDER, nullptr};    
    }

    OrgChart::Iterator OrgChart::begin() {
        if (this->root == nullptr) {
            throw invalid_argument("orgChart is empty");
        }
        return Iterator{LEVEL_ORDER, root};
    }

    OrgChart::Iterator OrgChart::end() {
        if (this->root == nullptr) {
            throw invalid_argument("orgChart is empty");
        }
        return Iterator{LEVEL_ORDER, nullptr};
    }

    void OrgChart::Iterator::reverse_builder(Node* root) {
        vector<Node*> temp_vec_for_fill; // push and pop for good order
        temp_vec_for_fill.push_back(root); // init with root
        for(unsigned int i= 0 ; i<temp_vec_for_fill.size() ; i++){ // loop over all nodes in temp
            Node* curr_node =  temp_vec_for_fill[i];
            for(int  j=(int)(*curr_node).get_sub().size()-1; j>=0; j--) { // fill with children in the oposite direction
                temp_vec_for_fill.push_back((*curr_node).get_sub().at((unsigned)j));
            }
        } 
        for(int i=(int)temp_vec_for_fill.size()-1 ; i>=0 ; i--) { // insert in the oposite direction
            iterator_list.push_back(temp_vec_for_fill.at((unsigned)i));
        }
    }

    OrgChart::Iterator OrgChart::begin_reverse_order() {
        if (this->root == nullptr) {
            throw invalid_argument("orgChart is empty");
        }
        return Iterator{REVERSE_LEVEL_ORDER, this->root};  
    }
    
    OrgChart::Iterator OrgChart::reverse_order() {
        if (this->root == nullptr) {
            throw invalid_argument("orgChart is empty");
        }
        return Iterator{REVERSE_LEVEL_ORDER, nullptr};  
    }

    void OrgChart::Iterator::preorder_builder(Node* root) {
        this->iterator_list.push_back(root); // add root to iterator
        unsigned int vector_size = (*root).get_sub().size();
        for(unsigned int i=0; i<vector_size; i++) { // add children
            Node* curr_node = (*root).get_sub().at(i);
            preorder_builder(curr_node); // recursively add all children og each child
        }
    }

    OrgChart::Iterator OrgChart::begin_preorder() {
        if (this->root == nullptr) {
            throw invalid_argument("orgChart is empty");
        }
        return Iterator{PRE_ORDER, root};    
    }
    
    OrgChart::Iterator OrgChart::end_preorder() {
        if (this->root == nullptr) {
            throw invalid_argument("orgChart is empty");
        }
        return Iterator{PRE_ORDER, nullptr}; 
    }

    void OrgChart::delete_OrgChart(Node *root) {
        if (this->root == nullptr) { 
            return; // orgchart is empty
        }
        if (!this->root->get_sub().empty()) {
            for (unsigned int i = 0; i < root->get_sub().size(); i++) {
                delete_OrgChart(root->get_sub()[i]); // recursevly delete all children
            }
        }
        delete root;
    }
}