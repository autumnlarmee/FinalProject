#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

//data will be the deciding factor
struct Node {
    int data;
    Node* left;
    Node* right;
};

//create new node
Node* createNode(int classifier) {
    Node* newNode = new Node();
    newNode->data = classifier;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

//returns vectors of patient data
void readData(vector<int>& gender, vector<int>& age,
vector<int>& education, vector<int>& currentSmoker, 
vector<int>& cigsPerDay, vector<int>& BPMeds, 
vector<int>& prevalentStroke, vector<int>& prevalentHyp,
vector<int>& diabetes, vector<int>& totChol, vector<int>& sysBP,
vector<int>& diaBP, vector<int>& BMI, vector<int>& heartRate,
vector<int>& glucose, vector<int>& TenYearCHD)
{
    string fileName;
    cout << "Enter your data file name: ";
    cin >> fileName;
    ifstream fin(fileName);
    
    string labels, line;
    getline(fin, labels);
    int iGender, iAge, iEducation, iCurrentSmoker, iCigsPerDay, iBPMeds,
    iPrevalentStroke, iPrevalentHyp, iDiabetes, iTotChol, iSysBP, iDiaBP, 
    iBMI, iHeartRate, iGlucose, iTenYearCHD;

    //for each patient
    while (getline(fin, line)) {
        stringstream lineStream(line);
        string value;

        getline(lineStream, value, ',');
        iGender = stoi(value);
        gender.push_back(iGender);

        getline(lineStream, value, ',');
        iAge = stoi(value);
        age.push_back(iAge);
        
        getline(lineStream, value, ',');
        iEducation = stoi(value);
        education.push_back(iEducation);

        getline(lineStream, value, ',');
        iCurrentSmoker = stoi(value);
        currentSmoker.push_back(iCurrentSmoker);

        getline(lineStream, value, ',');
        iCigsPerDay = stoi(value);
        cigsPerDay.push_back(iCigsPerDay);

        getline(lineStream, value, ',');
        iBPMeds = stoi(value);
        BPMeds.push_back(iBPMeds);

        getline(lineStream, value, ',');
        iPrevalentStroke = stoi(value);
        prevalentStroke.push_back(iPrevalentStroke);

        getline(lineStream, value, ',');
        iPrevalentHyp = stoi(value);
        prevalentHyp.push_back(iPrevalentHyp);

        getline(lineStream, value, ',');
        iDiabetes = stoi(value);
        diabetes.push_back(iDiabetes);

        getline(lineStream, value, ',');
        iTotChol = stoi(value);
        totChol.push_back(iTotChol);

        getline(lineStream, value, ',');
        iSysBP = stoi(value);
        sysBP.push_back(iSysBP);

        getline(lineStream, value, ',');
        iDiaBP= stoi(value);
        diaBP.push_back(iDiaBP);

        getline(lineStream, value, ',');
        iBMI = stoi(value);
        BMI.push_back(iBMI);

        getline(lineStream, value, ',');
        iHeartRate = stoi(value);
        heartRate.push_back(iHeartRate);

        getline(lineStream, value, ',');
        iGlucose = stoi(value);
        glucose.push_back(iGlucose);

        getline(lineStream, value, ',');
        iTenYearCHD = stoi(value);
        TenYearCHD.push_back(iTenYearCHD);
    }
}

//returns a classifier value (value to compare to)
int classifier(vector<int>& variable, vector<int>& TenYearCHD) {
    vector<int> predictor, nonpredictor;
    //for each patient in training data set
    for (int i = 0; i < variable.size(); i++) {
        //if there was CHD in the next 10 years
        if (TenYearCHD[i] == 1) {
            //add the variable value to predictor vector
            predictor.push_back(variable[i]);
        }
        else {
            nonpredictor.push_back(variable[i]);
        }
    }
    auto p = minmax_element(nonpredictor.begin(), nonpredictor.end());
    auto t = minmax_element(predictor.begin(),predictor.end());
    double result = (*p.second + *t.first) / 2;
    return result;
}

int main() {
    vector<int> gender, age, education, currentSmoker, 
    cigsPerDay, BPMeds, prevalentStroke, prevalentHyp,
    diabetes, totChol, sysBP, diaBP, BMI, heartRate,
    glucose, TenYearCHD;
    readData(gender, age, education, currentSmoker, 
    cigsPerDay, BPMeds, prevalentStroke, prevalentHyp,
    diabetes, totChol, sysBP, diaBP, BMI, heartRate,
    glucose, TenYearCHD);

    for (int i = 0; i < gender.size(); i++) {
        cout << gender[i] << " ";
    }

}

