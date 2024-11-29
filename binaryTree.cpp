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

/*returns a classifier value (value to compare to) for the best split on this variable, and a value
  for the quality of this variable's best split (in case we want to consider multiple variables to split on), respectively. 
  The higher the latter value, the worse, which is all that is relevant about that value.
  If the list of data is too small for the algorithm to desire to make a split, both elements of the pair will be -1.

  We do it by evaluating all possible ways to split the data into two groups. For each split, we compare
  the average of TenYearCHD's in each group to each of the individual TenYearCHD's in that group, and use 
  this evaluation from both groups to try to determine how unambiguous the interpretation of TenYearCHD correlation 
  of both groups will be if we make this split. We choose the best split for our single-variable list of data in this way,
  and return where the split should be made.
*/
pair<double, double> classifierSingleVar(vector<int>& variable, vector<int>& TenYearCHD) {
    int MIN_SPLIT_SIZE = 5; //min size for each of the two groups the split would leave.

    int patientsN = TenYearCHD.size();

    pair<double, double> bestScoreAndClassifier = {-1, -1};
    for(int spliti=MIN_SPLIT_SIZE; spliti<=patientsN-2-MIN_SPLIT_SIZE; spliti++){ //we split the total group between two items. spliti is the left item's index
        vector<int> group1(TenYearCHD.begin(), TenYearCHD.begin() + spliti + 1);
        vector<int> group2(TenYearCHD.begin() + spliti + 1, TenYearCHD.end());
        double splitBadness = ambiguityMetric(group1) + ambiguityMetric(group2);
        if(bestScoreAndClassifier.first == -1 || (splitBadness < bestScoreAndClassifier.first)){
            bestScoreAndClassifier = {splitBadness, (TenYearCHD.at(spliti) + TenYearCHD.at(spliti + 1)) / (double) (2)};
        }
    }

    return {-1, -1}; //should exclusively occur if patientsN < MIN_SPLIT_SIZE * 2 ???

}

/*
Used when determining splits, for evaluating how well the split splits us on something potentially
real vs something uncorellated and ambiguous. Call on a list of target variables. High return value is bad, low is good.
*/
double ambiguityMetric(vector<int> group){
    // Uses mean squared error.

    // avg of set
    double avg;
    for(int i=0; i<group.size(); i++){
        avg += group.at(i);
    }
    avg = avg / (double) (group.size());

    // sum of squared differences between element and set average
    double sum = 0;
    for(int i=0; i<group.size(); i++){
        double a = group.at(i) - avg;
        sum += a * a;
    }
    return sum / group.size();
}


/*
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
*/

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

int predict(Node* root, vector<double>& userInput) {
    int score = 0;
    for (int i = 0; i < userInput.size() - 1; i++) {
        if (userInput[i] > root->data) {
            score += 1;
            root = root->right;
        }
        else {
            root = root->left;
        }
    }
    return score;
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
    double iGender, iAge, iEducation, iCurrentSmoker, iCigsPerDay, iBPMeds,
    iPrevalentStroke, iPrevalentHyp, iDiabetes, iTotChol, iSysBP, iDiaBP, 
    iBMI, iHeartRate, iGlucose, iTenYearCHD;
    vector<double> userInput;

    cout << "Enter name: ";
    cin >> name;
    cout << "M or F? (enter 1 or 0): ";
    cin >> iGender;
    userInput.push_back(iGender);
    cout << "Enter age: ";
    cin >> iAge;
    userInput.push_back(iAge);
    cout << "Enter education level (1-4): ";
    cin >> iEducation;
    userInput.push_back(iEducation);
    cout << "Are you a current smoker? (enter 1 or 0): ";
    cin >> iCurrentSmoker;
    userInput.push_back(iCurrentSmoker);
    cout << "How many cigs do you smoke per day? ";
    cin >> iCigsPerDay;
    userInput.push_back(iCigsPerDay);
    cout << "Are you on blood pressure meds? (enter 1 or 0): ";
    cin >> iBPMeds;
    userInput.push_back(iBPMeds);
    cout << "Do you have prevalent strokes? (enter 1 or 0): ";
    cin >> iPrevalentStroke;
    userInput.push_back(iPrevalentStroke);
    cout << "Do you have prevalent hypertension? (enter 1 or 0): ";
    cin >> iPrevalentHyp;
    userInput.push_back(iPrevalentHyp);
    cout << "Do you have diabetes? (enter 1 or 0): ";
    cin >> iDiabetes;
    userInput.push_back(iDiabetes);
    cout << "What is your total cholesterol? (50-400): ";
    cin >> iTotChol;
    userInput.push_back(iTotChol);
    cout << "What is your systolic blood pressure? (50-200): ";
    cin >> iSysBP;
    userInput.push_back(iSysBP);
    cout << "What is your diastolic blood pressure? (40-200): ";
    cin >> iDiaBP;
    userInput.push_back(iDiaBP);
    cout << "What is your body mass index? (15-50): ";
    cin >> iBMI;
    userInput.push_back(iBMI);
    cout << "What is your heart rate? (20-200): ";
    cin >> iHeartRate;
    userInput.push_back(iHeartRate);
    cout << "What is your glucose level? (50-200): ";
    cin >> iGlucose;
    userInput.push_back(iGlucose);

    cout << endl << "Predicting chances of coronary heart disease within the next 10 years..." << endl << endl;
    int score = predict(root, userInput);
    cout << "Your chances of CHD are: " << (score / 15) * 100 << "%" << endl;
}



