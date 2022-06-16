#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
#include "OrgChart.hpp"
using namespace ariel;

int main() {
   OrgChart org_chart;
   string root;
   cout << "enter OrgChart ROOT"<<endl;
   cin >> root;
   org_chart.add_root(root);
   while (1){
       string father;
       string son;
       cout << "enter FATHER from OrgChart" << endl;
       cin >> father;
       cout <<"enter a SON for this father" << endl;
       cin >> son;
       try{
           org_chart.add_sub(father, son);
       }
       catch (const std::exception &e){
           break;
       }
   }

   while (1){
       string str;
       cout<<"enter your iterator:\nL - Level Order\nP - Pre Order\nR - Reverse Order\nother key to exit"<<endl;
       cin>>str;
       if (str=="L"){
           for (auto temp = org_chart.begin_level_order(); temp != org_chart.end_level_order(); ++temp) {
               cout << (*temp) << " ";

           }
           cout << " " << endl;
       }
       else if (str=="P"){
           for (auto temp = org_chart.begin_preorder(); temp != org_chart.end_preorder(); ++temp) {
               cout << (*temp) << " ";
           }
           cout << " " << endl;
       }
       else if (str=="R"){
           for (auto temp = org_chart.begin_reverse_order(); temp != org_chart.reverse_order(); ++temp) {
               cout << (*temp) << " ";
           }
           cout << " " << endl;
       }
       else{
           exit(1);
       }
   }
   return 0;
}




