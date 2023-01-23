#include <bits/stdc++.h>

using namespace std;

string header, footer;

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

vector <vector<pair<int,int>>> getPoints(vector <vector<pair<int,int>>> actual_pts, vector <pair<int,int>> tp_points, bool first, bool f, bool s, bool poly, fstream &file){
    int fnum , snum;
    if(file.is_open()){
        string temp;
        while(file >> temp) { //take word and print

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
                actual_pts.push_back(tp_points);
                tp_points.clear();
            }

        }

        file.close();
    }
    return actual_pts;
}

void getHeader_and_Footer(fstream &file, bool head, bool foot){
    if(file.is_open()){
        string temp , temp_header;
        while(getline(file, temp)){ 
           
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

        file.close();
    }
}

int main(){

    std::ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    fstream newFile, tempFile , outFile, resFile;
    string filename = "Milestone_Input/Milestone 5/Source.txt";
    string resFileName = "Milestone_Input/Milestone 5/POI.txt";
    newFile.open(filename.c_str());
    tempFile.open(filename);
    resFile.open(resFileName);

    // string header, footer;
    bool head = false , foot = false , poly = false, first = true, f=true, s=false;
    
    // Get the points from all the polygons.
    
    vector <vector<pair<int,int>>> points;
    vector <pair<int,int>> tp_points;
    points = getPoints(points,tp_points,first,f,s,poly,newFile);

    // Get the header and footer.

    getHeader_and_Footer(tempFile,head,foot);
     

    vector <vector<pair<int,int>>> res_points;
    vector <pair<int,int>> res_tp_points;
    first = true; f=true; s=false; poly = false;
    res_points = getPoints(res_points,res_tp_points,first,f,s,poly,resFile);

    // Get the actual area of POI.

    double actual_res;
    for(int i=0 ; i<res_points.size() ; i++){
        vector <double> X,Y;
        for(auto it : res_points[i]){
            X.push_back(it.first);
            Y.push_back(it.second);
        }
        actual_res = polygonArea(X,Y,res_points[i].size());
    }

    // Get the matches.
    
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

    cout<<match_count<<"\n";

    // Output to the result file.

    outFile.open("MileStone_Output/m5out.txt");
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