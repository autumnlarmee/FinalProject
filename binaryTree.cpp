/*
<<<<<<< Updated upstream
Explanation:
very in-progress. It's based on the standard regression tree algorithm. You start with a node with all predictive data for all patients in it,
=======
todo: better description at top. Name is not used but asked for on cin, but I personally like that.

It's based on the standard regression tree algorithm. You start with a node with all predictive data for all patients in it,
>>>>>>> Stashed changes
and all target data for all patients. You brute force all variables and all positions in all variables to find the one that would make
the best split, meaning, we calculate how well each split seems to say something about the data - how strongly correlated to one value for
the target one half would be, and the other for the other half. Choose the best split like that... variable and point that makes best split.

of course, it's recursive, so this is assuming we had not met some criteria for saying we're a leaf node yet. I'm saying it's when 
we don't have more than a certain amount of data points in our node.

Once our tree is done, branch nodes represent choices, and leaf nodes represent probability of CHD - because we take the average of the target
variables left in the leaf node - 0's and 1's - and get a proportion of people in that leaf cohort (the result of narrowing down along lots
of criteria we thought were good to differentiate by) who have TenYearCHD. So, that is an estimated probability when we are inputting our
new patient on the console and asking for a probability.

*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <set>
#include <iomanip>
using namespace std;


struct Node {
    //classifier will be the deciding factor. This is like "age > 3.5?" val is the 3.5 number here, vari is the "age" specification.
    // greater than (>), go to right node (>), less than (<), go to left node (<).
    int classifiervari; /* -1 lets you know this is a leaf node. In this case, most other variables will likely become useless.
                           TenYearCHDForPatientsHere will still be used to take an average as our estimated probability that a new patient
                           reaching this node has TenYearCHD */
    double classifierval;

    Node* left;
    Node* right;

    //as we progress with tree generation, deepening down, narrowing down on additional specific qualities that are correlated with our target variable,
    //we narrow down the patients at each node. These 2 vectors essentially represent smaller versions
    //of our original csv file - the patients relevant to this node, after all of the splits before it.
    vector<vector<int>> variablesForPatientsHere;
    vector<int> TenYearCHDForPatientsHere;
};

Node* createNode(int classifiervari, double classifierval, vector<vector<int>> variablesForPatientsHere, vector<int> TenYearCHDForPatientsHere) {
    Node* newNode = new Node();
    newNode->classifiervari = classifiervari;
    newNode->classifierval = classifierval;
    newNode->left = newNode->right = nullptr;
    newNode->variablesForPatientsHere = variablesForPatientsHere;
    newNode->TenYearCHDForPatientsHere = TenYearCHDForPatientsHere;
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

/*
Used when determining splits, for evaluating how well the split splits us on something potentially
real vs something uncorellated and ambiguous. Call on a list of target variables. High value is bad, low is good.
*/
double ambiguityMetric(vector<int> group){
    // Uses mean squared error.

    // avg of set
    double avg = 0.0;
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

/* Takes two unsorted lists: forComparisons, and forOutput. Splits the forComparisons list so that items less than classifier
are in a "left" list and items more than classifier are in a "right" list. Now, return these two split lists as {leftlist, rightlist},
but return the forOutput values that correspond to the forComparisons values (so if an item in forOutput had the same
id as an item in forComparisons when the lists were passed to the function, those are "corresponding" items).
*/
pair<vector<int>, vector<int>> binarySplit(vector<int>& forComparisons, vector<int>& forOutput, double classifier){

    vector<int> left;
    vector<int> right;

    for(int i=0; i<forComparisons.size(); i++){
        if(forComparisons.at(i) < classifier){
            left.push_back(forOutput.at(i));
        }else{
            right.push_back(forOutput.at(i));
        }
    }

    return {left, right};

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
    const int MIN_SPLIT_CHILD_SIZE = 20; //min size for each of the two groups the split would leave.

    int patientsN = TenYearCHD.size();

    // come up with all potential split points(classifiers) as midpoints between values in variable<> when sorted and duplicates removed.
    set<int> sortedVariable(variable.begin(), variable.end());
    vector<double> potClassifiers;
    for (set<int>::iterator splitLItem = sortedVariable.begin(); splitLItem != prev(sortedVariable.end()); splitLItem++) {
        set<int>::iterator splitRItem = next(splitLItem);
        potClassifiers.push_back((*splitLItem + *splitRItem) / (double) (2)); // midpoint between these two data as classifier?
    }

    // check all of those potential classifiers to see which is the best
    pair<double, double> bestClassifierAndScore = {-1, -1};
    for(int i=0; i<potClassifiers.size(); i++){
        double classifier = potClassifiers.at(i);
        
        // make a split at this classifier in the variable data.
        pair<vector<int>, vector<int>> leftnright = binarySplit(variable, TenYearCHD, classifier);
        // If it does not result in children of adequate size, discard it.
        if(leftnright.first.size() < MIN_SPLIT_CHILD_SIZE || leftnright.second.size() < MIN_SPLIT_CHILD_SIZE)continue;
        
        // from the TenYearCHD data corresponding to each side of the split on our variable data, calculate numerically how good a split
        // it was. update our best potential return value if we found a new best split.
        double splitBadness = ambiguityMetric(leftnright.first) + ambiguityMetric(leftnright.second);
        if(bestClassifierAndScore.second == -1 || (splitBadness < bestClassifierAndScore.second)){
            bestClassifierAndScore = {classifier, splitBadness};
        }
    }
    
    return bestClassifierAndScore;
}

/*
For branch nodes in our regression tree.
Determines best variable and position to make a binary split on.
Returns a classifier value to arrange a split around, and an index of which variable to split on, respectively.
If no variables are splittable (not enough data points for any of them), you'll get back {-1, -1}.
(That's when you would make the node you're calling this for a leaf node).
*/
pair<double, int> classifierMultiVar(vector<vector<int>>& vars, vector<int>& TenYearCHD){
    /* iterate all variables, classifierSingleVar() them, return a classifier and var index for whatever var is smartest to split on according to
       classifierSingleVar()s' badness scores. */
    pair<int, pair<double, double>> bestVarToSplit = {-1, {-1, -1}}; // index of var, {classifier for its best split, badness of its best split}
    for(int v=0; v<vars.size(); v++){
        pair<double, double> classifierAndBestScore = classifierSingleVar(vars.at(v), TenYearCHD);
        if(classifierAndBestScore.first != -1 && (bestVarToSplit.first == -1 || (classifierAndBestScore.second < bestVarToSplit.second.second))){
            bestVarToSplit = {v, classifierAndBestScore};
        }
    }
    return {bestVarToSplit.second.first, bestVarToSplit.first};
}

Node* createTree(vector<int>& TenYearCHD, vector<vector<int>>& variables){
    // question at this node. "variable < or > a value?"
    pair<double, int> classifier = classifierMultiVar(variables, TenYearCHD);

    // This is recursive. Here, we make ourselves. Later, we'll consider making our children.
    Node* node = createNode(classifier.second, classifier.first, variables, TenYearCHD);

    if(classifier.first == -1) return node; // we a leaf node
    // else, we a branch node

    // for all of our variables, and for TenYearCHD, see what would happen if we split our classification variable
    // along its classification value. Whatever happens, that is how we split each of these lists. This is of course just
    // to carry data related to the same person to the same side, since we'll be sending to left/right nodes soon.
    vector<int> determiningVariable = variables.at(classifier.second);
    pair<vector<int>, vector<int>> TenYearCHDSplit = binarySplit(determiningVariable, TenYearCHD, classifier.first);
    vector<pair<vector<int>, vector<int>>> variablesSplit;
    for(int v=0; v<variables.size(); v++){
        variablesSplit.push_back(binarySplit(determiningVariable, variables.at(v), classifier.first));
    }

    pair<vector<vector<int>>, vector<vector<int>>> variablesSplit2; // same thing but can pass to createTree.
    for(auto v : variablesSplit){
        variablesSplit2.first.push_back(v.first);
        variablesSplit2.second.push_back(v.second);

    }

    //cout << "splitting based on var #" << classifier.second << " around " << classifier.first << ": " << TenYearCHDSplit.first.size() << " < | > " << TenYearCHDSplit.second.size() << endl;

    // kids
    node->left = createTree(TenYearCHDSplit.first, variablesSplit2.first);
    node->right = createTree(TenYearCHDSplit.second, variablesSplit2.second);

    return node;

}

/*
void printInOrder(Node* root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << root->classifier << " ";
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
        cout << currentNode->classifier << " ";

        if (currentNode->left) {
            q.push(currentNode->left);
        }

        if (currentNode->right) {
            q.push(currentNode->right);
        }
    }
    cout << endl;
}
*/

// root node of a tree, and a vector of ints for user data in the same order (and nothing missing or extra) and the same meaning
// of numbers (eg 1 means male, 0 female (i think)) that we have in our csv.
double predict(Node* root, vector<int>& variables) {
    double prediction = 0.0;
    int level = 0;
    while(true){
        // leaf node, so return a prediction
        if(root->classifiervari == -1) {
            // by taking average of the TenYearCHDs for all the patients that were in this leaf at training. That's our estimated probability
            // that somebody new that gets to this class has it.
            for(int chd : root->TenYearCHDForPatientsHere){
                prediction += chd;
            }
            prediction /= root->TenYearCHDForPatientsHere.size();
            break;
        }

        // branch node, so compare ourselves to the classifier and move along the tree accordingly.
        int variable = variables.at(root->classifiervari);
        if(variable < root->classifierval){
            root = root->left;
        }else {
            root = root->right;
        }
        level++;
    }
    return prediction;
}

// used in main to help with taking user input.
// we ask on command line stuff like "Enter education level (1-4): ".
// This has to be in a range, and if not, we'll re-ask it. So, to make this process repeatable, we define
// questions with this, then ask questions with the same code.
struct VariableInputInformation{
    // in the question "Enter education level (1-4): "...
    string query; // ...that string exactly...
    int* real; // ...the actual code variable for education level...
    int min; // ...1...
    int max; // ...4.
};

// grab a positive int that we want in a certain range (inclusive, inclusive) from cin. If it is out of range, return -1 for error.
int cinIntPosInRange(int min, int max){
    int val;
    cin >> val;

    if(val < min || val > max)return -1;
    return val;
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

    cout << "Okay, generating tree..." << endl;
    Node* root = createTree(TenYearCHD, variables);
    cout << "...Done!" << endl;

    //interact with user
    string name;
    int iMale=-1, iAge=-1, iEducation=-1, iCurrentSmoker=-1, iCigsPerDay=-1, iBPMeds,
    iPrevalentStroke=-1, iPrevalentHyp=-1, iDiabetes=-1, iTotChol=-1, iSysBP=-1, iDiaBP=-1, 
    iBMI=-1, iHeartRate=-1, iGlucose=-1;
    vector<int> userInput;
    VariableInputInformation questions[] = { // will all be output with a ": " after. 
        {"Are you male", &iMale, 0, 1},
        {"Enter age", &iAge, -1, -1},
        {"Enter education level", &iEducation, 1, 4},
        {"Are you a current smoker", &iCurrentSmoker, 0, 1},
        {"How many cigs do you smoke per day", &iCigsPerDay, -1, -1},
        {"Are you on blood pressure meds", &iBPMeds, 0, 1},
        {"Do you have prevalent strokes", &iPrevalentStroke, 0, 1},
        {"Do you have prevalent hypertension", &iPrevalentHyp, 0, 1},
        {"Do you have diabetes", &iDiabetes, 0, 1},
        {"What is your total cholesterol", &iTotChol, 50, 400},
        {"What is your systolic blood pressure", &iSysBP, 50, 200},
        {"What is your diastolic blood pressure", &iDiaBP, 40, 200},
        {"What is your body mass index", &iBMI, 15, 50},
        {"What is your heart rate", &iHeartRate, 20, 200},
        {"What is your glucose level", &iGlucose, 50, 200}
    };
    
    cout << "Enter name: ";
    cin >> name;
    
    // ask all my questions and get all my user input health data.
    for(VariableInputInformation question : questions){
        // until i get valid input...
        while(*question.real == -1){
            // output question string
            cout << question.query;
            if(question.min != -1 && question.max != -1)
                cout << "(" << question.min << (question.max - question.min == 1 ? " or " : "-") << question.max << ")";
            cout << ": ";

            // try to take input
            if(question.min == -1 || question.max == -1) 
                cin >> *question.real;
            else 
                *question.real = cinIntPosInRange(question.min, question.max);
        }
        userInput.push_back(*question.real);
    }
    
    // predict chance and output it.
    cout << endl << "Predicting chances of coronary heart disease within the next 10 years..." << endl << endl;
    double chance = predict(root, userInput);
    cout << "Your chances of CHD are: " << (int) (chance * 100 + 0.5) << "%" << endl;

}



