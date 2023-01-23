#include <bits/stdc++.h>

using namespace std;

#define PI 3.14159265
#define pdd pair<double, double>

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

vector <double> trueShape(vector <double> &X, vector <double> &Y, int n){
    vector <double> sides;
    for(int i=0 ; i<n-1 ; i++){
        double sidelen = sqrt(pow(X[i+1]-X[i],2) + pow(Y[i+1]-Y[i],2));
        sides.push_back(sidelen);
    }
    double sidelen = sqrt(pow(X[n-2]-X[n-1],2)+pow(Y[n-2]-Y[n-1],2));
    sides.push_back(sidelen);
    sort(sides.begin(),sides.end());
    return (sides);
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

vector <double> getAngles(vector <double> &X, vector <double> &Y, int n){
    double m1, A, m2, B;
    vector <double> ang;
    for(int i=0 ; i<n-2 ; i++){
        m1 = (Y[i+1] - Y[i]) / (X[i+1] - X[i]);
        A = atan(m1) * 180 / PI;
        m2 = (Y[i+2] - Y[i+1]) / (X[i+2] - X[i+1]);
        B = atan(m2) * 180 / PI;
        ang.push_back(A-B);
    }

    m1 = (Y[n-1] - Y[n-2]) / (X[n-1] - X[n-2]);
    A = atan(m1) * 180 / PI;
    m2 = (Y[0] - Y[n-1]) / (X[0] - X[n-1]);
    B = atan(m2) * 180 / PI;
    ang.push_back(A-B);
   
    m1 = (Y[0] - Y[n-1]) / (X[0] - X[n-1]);
    A = atan(m1) * 180 / PI;
    m2 = (Y[1] - Y[0]) / (X[1] - X[0]);
    B = atan(m2) * 180 / PI;
    ang.push_back(A-B);

    sort(ang.begin(),ang.end());
    return (ang);
}

pdd IntersectionPoint(pdd A, pdd B, pdd C, pdd D)
{
	double a1 = B.second - A.second;
	double b1 = A.first - B.first;
	double c1 = a1*(A.first) + b1*(A.second);

	double a2 = D.second - C.second;
	double b2 = C.first - D.first;
	double c2 = a2*(C.first)+ b2*(C.second);

	double determinant = a1*b2 - a2*b1;

	if (determinant == 0)
		return make_pair(FLT_MAX, FLT_MAX);

	else
	{
		double x = (b2*c1 - b1*c2)/determinant;
		double y = (a1*c2 - a2*c1)/determinant;
		return make_pair(x, y);
	}
}

int intersectionArea(vector <double> &X, vector <double> &Y, int n){
    vector <double> newX , newY;
    for(int i=0 ; i<n-2 ; i++){
        pdd A = {X[i],Y[i]};
        pdd B = {X[i+1],Y[i+1]};
    }
}

// 4950 - Expected Answer.

int main(){

    std::ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    fstream newFile, tempFile , outFile, resFile;
    string filename = "Milestone_Input/Milestone 6/Source.txt";
    string resFileName = "Milestone_Input/Milestone 6/POI.txt";
    newFile.open(filename.c_str());
    tempFile.open(filename);
    resFile.open(resFileName);

    string header, footer, polygons;
    bool head = false , foot = false , poly = false, first = true, f=true, s=false;
    
    // Get the actual points.

    vector <vector<pair<int,int>>> points;
    vector <pair<int,int>> tp_points;
    points = getPoints(points,tp_points,first,f,s,poly,newFile);
    
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


    // Getting result points.
    vector <vector<pair<int,int>>> res_points;
    vector <pair<int,int>> res_tp_points;
    first = true; f=true; s=false; poly = false;
    res_points = getPoints(res_points,res_tp_points,first,f,s,poly,resFile);

    
    // Get the actual areas.
    
    double actual_res_area;
    vector <double> res_areas;
    for(int i=0 ; i<res_points.size() ; i++){
        vector <double> X,Y;
        for(auto it : res_points[i]){
            X.push_back(it.first);
            Y.push_back(it.second);
        }
        res_areas.push_back(polygonArea(X,Y,res_points[i].size()));
    }

    
    // Get the matches.
    
    int match_count = 0;
    vector <bool> matches;
    vector <vector<double>> cs;
    vector <double> ratios;
    bool poly1 = true , poly2 = true;
    bool poly11 = true , poly22 = true;

    for(int i=0 ; i<points.size() ; i++){
        vector <double> X,Y;
        for(auto it : points[i]){
            X.push_back(it.first);
            Y.push_back(it.second);
        }
        double res = polygonArea(X,Y,points[i].size());
        
        vector <double> curr_sides = trueShape(X,Y,points[i].size());
        cs.push_back(curr_sides);
       
        double ratio = res / res_areas[0];
        ratios.push_back(ratio);
        if(ratio == 1.0 || ratio == 2.25 || ratio == 0.25){
            match_count++;
            matches.push_back(true);
        }
    
        else
            matches.push_back(false);
    }

    cout<<match_count<<endl;
    
    // Write to output file.

    outFile.open("MileStone_Output/m6out.txt");
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