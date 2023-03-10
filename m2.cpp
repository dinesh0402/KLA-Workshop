#include <bits/stdc++.h>

using namespace std;

bool isNumber(const string& s){
    return s.find_first_not_of("-9-8-7-6-5-4-3-2-10123456789") == string::npos;
}

double polygonArea(vector <double> &X, vector <double> &Y, int n)
{
    double area = 0.0;
 
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (X[j] + X[i]) * (Y[j] - Y[i]);
        j = i; 
    }

    return abs(area / 2.0);
}

int main(){

    fstream newFile, tempFile , outFile, resFile;
    string filename = "Milestone_Input/Milestone 2/Source.txt";
    string resFileName = "Milestone_Input/Milestone 2/POI.txt";
    newFile.open(filename.c_str());
    tempFile.open(filename);
    resFile.open(resFileName);

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

        newFile.close();
    }

    vector <vector<pair<int,int>>> res_points;
    vector <pair<int,int>> res_tp_points;
    first = true; f=true; s=false; poly = false;

    if(resFile.is_open()){
        string temp;
        while(resFile >> temp) { //take word and print

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
                            res_tp_points.push_back({fnum,snum});
                        }

                    }
                }
                poly = true;
            }

            if(temp == "endel"){
                poly = false;
                first = true;
                res_points.push_back(res_tp_points);
                res_tp_points.clear();
            }

        }

        resFile.close();
    }

    double actual_res;
    for(int i=0 ; i<res_points.size() ; i++){
        vector <double> X,Y;
        for(auto it : res_points[i]){
            X.push_back(it.first);
            Y.push_back(it.second);
        }
        actual_res = polygonArea(X,Y,res_points[i].size());
    }

    int match_count = 0;
    vector <bool> matches;
    for(int i=0 ; i<points.size() ; i++){
        vector <double> X,Y;
        for(auto it : points[i]){
            X.push_back(it.first);
            Y.push_back(it.second);
        }
        double res = polygonArea(X,Y,points[i].size());
        if(res == actual_res){
            match_count++;
            matches.push_back(true);
        }
        else
            matches.push_back(false);
    }

    // cout<<match_count<<endl;

    

    outFile.open("MileStone_Output/m2out.txt");
    if(outFile.is_open()){
        outFile<<header;
        outFile<<endl;

        for(int i=0 ; i<matches.size() ; i++){
            
            if(matches[i]){
                outFile<<"boundary\n";
                outFile<<"layer 1\n";
                outFile<<"datatype 0\n";
                outFile<<"xy  "<<to_string(points[i].size());
                for(auto it : points[i]){
                    outFile<<"  "<<to_string(it.first)<<" "<<to_string(it.second)<<"  ";
                }
                outFile<<"\nendel\n";
            }
        }

        outFile<<footer;
        outFile.close();
    }

    return (0);
}