#include <bits/stdc++.h>

using namespace std;

bool isNumber(const string& s){
    return s.find_first_not_of("-9-8-7-6-5-4-3-2-10123456789") == string::npos;
}

int main(){

    fstream newFile, tempFile , outFile;
    string filename = "Milestone_Input/Milestone 1/Format_Source.txt";
    newFile.open(filename.c_str());
    tempFile.open(filename);

    string header, footer, polygons;
    bool head = false , foot = false , poly = false, first = true, f=true, s=false;
    vector <vector<pair<int,int>>> points;
    vector <pair<int,int>> tp_points;
    int fnum , snum;

    if(tempFile.is_open()){
        string temp , temp_header;
        while(getline(tempFile, temp)){ 
           
            if(temp[0] == 'h' || head == true){
                temp_header += temp + "\n";
                head = true;
            }

            if(temp[0] == 's' && temp[temp.size()-1] == 'p'){
                temp_header += temp + "\n";
                head = false;
            }

            if((temp[0] == 'e' && temp[temp.size()-1] == 'r') || foot == true){
                footer += temp + "\n";
                foot = true;
            }
        }

        for(int i=0 ; i<temp_header.size()-12 ; i++)
            header += temp_header[i];

        // cout<<"The Header is : \n";
        // cout<<header<<endl;
        
        // cout<<"The Footer is : \n";
        // cout<<footer<<endl;

        tempFile.close();
    }

    if(newFile.is_open()){
        string temp;
        while(newFile >> temp) { //take word and print

            if(temp == "xy" || poly == true){
                if(isNumber(temp)){
                    if(first){
                        first = false;
                        continue;
                    }
                    else{
                        if(f){
                            fnum = stoi(temp);
                            f = false;
                            s = true;
                        }
                        else{
                            snum = stoi(temp);
                            s = false;
                            f = true;
                        }

                        if(f && !s){
                            tp_points.push_back({fnum,snum});
                        }

                    }
                }
                poly = true;
            }

            if(temp == "endel"){
                poly = false;
                first = true;
                points.push_back(tp_points);
                tp_points.clear();
            }

        }

        // cout<<"The first 2 polygons are : \n";
        // for(int i=0 ; i<2 ; i++){
        //     for(auto it : points[i])
        //         cout<<it.first<<" "<<it.second<<endl;
        //     cout<<endl;
        // }

        newFile.close();
    }

    outFile.open("MileStone_Output/m1out.txt");
    if(outFile.is_open()){
        outFile<<header;
        outFile<<endl;

        for(int i=0 ; i<2 ; i++){
            outFile<<"boundary\n";
            outFile<<"layer 1\n";
            outFile<<"datatype 0\n";
            outFile<<"xy  "<<to_string(points[i].size());
            for(auto it : points[i]){
                outFile<<"  "<<to_string(it.first)<<" "<<to_string(it.second)<<"  ";
            }
            outFile<<"\nendel\n";
        }

        outFile<<footer;
        outFile.close();
    }

    return (0);
}