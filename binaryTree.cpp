#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

//data will be the deciding factor
struct Node {
    double data;
    Node* left;
    Node* right;
};

//create new node
Node* createNode(double classifier) {
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
vector<int>& glucose, vector<int>& TenYearCHD, vector<vector<int>>& variables)
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
    variables.push_back(gender);
    variables.push_back(age);
    variables.push_back(education);
    variables.push_back(currentSmoker);
    variables.push_back(cigsPerDay);
    variables.push_back(BPMeds);
    variables.push_back(prevalentStroke);
    variables.push_back(prevalentHyp);
    variables.push_back(diabetes);
    variables.push_back(totChol);
    variables.push_back(sysBP);
    variables.push_back(diaBP);
    variables.push_back(BMI);
    variables.push_back(heartRate);
    variables.push_back(glucose);
}

//returns a classifier value (value to compare to)
double classifier(vector<int>& variable, vector<int>& TenYearCHD) {
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
    //cout << *p.second << " " << *t.first << endl;
    double sum = *p.second + *t.first;
    double result = sum / 2;
    return result;
}

Node* createTree(int depth, vector<int>& TenYearCHD, vector<vector<int>>& variables, int counter) {
    if (depth == 0) {
        return nullptr;
    }
    double iClassifier = classifier(variables[counter], TenYearCHD);
    Node* node = createNode(iClassifier);

    //decrease depth, increase counter (next variable on next level)
    node->left = createTree(depth - 1, TenYearCHD, variables, counter + 1);
    node->right = createTree(depth - 1, TenYearCHD, variables, counter + 1);
    return node;
}

void printInOrder(Node* root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << root->data << " ";
        printInOrder(root->right);
    }
}

//print each level in order
void printLevelOrder(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* currentNode = q.front();
        q.pop();
        cout << currentNode->data << " ";

        if (currentNode->left) {
            q.push(currentNode->left);
        }

        if (currentNode->right) {
            q.push(currentNode->right);
        }
    }
    cout << endl;
}

int main() {
    vector<int> gender, age, education, currentSmoker, 
    cigsPerDay, BPMeds, prevalentStroke, prevalentHyp,
    diabetes, totChol, sysBP, diaBP, BMI, heartRate,
    glucose, TenYearCHD;
    vector<vector<int>> variables;

    //read in data to vectors
    readData(gender, age, education, currentSmoker, 
    cigsPerDay, BPMeds, prevalentStroke, prevalentHyp,
    diabetes, totChol, sysBP, diaBP, BMI, heartRate,
    glucose, TenYearCHD, variables);

    //classifiers and constants
    int cGender, cAge, cEducation, cCurrentSmoker, 
    cCigsPerDay, cBPMeds, cPrevalentStroke, cPrevalentHyp,
    cDiabetes, cTotChol, cSysByp, cDiaBP, cBMI, cHeartRate, 
    cGlucose, cTenYearCHD;
    int depth = 14;
    int counter = 0;

    Node* root = createTree(depth, TenYearCHD, variables, counter);
    printLevelOrder(root);

    //interact with user
    string name;
    cout << "Hello patient! Enter name: ";
    cin >> name;
    
}


