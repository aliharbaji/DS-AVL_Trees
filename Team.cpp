//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"
#include <iostream>



//int Team::getMedals() const {
//    return medals;
//}

int Team::getStrength() const {
    int value = ( (getNumberOfContestants() > 0) && ((getNumberOfContestants() % 3) == 0) ) ? strength : 0;
    return value;
}

int Team::getNumberOfContestants() const {
    return contestants->getSize();
}


void Team::removeTeamFromItsCountry() {
    myCountry.lock()->removeTeam();
}

Sport Team::getSport() const {
    return sport;
}

int Team::getCountryID() const {
    return myCountry.lock()->getID();
}

void Team::moveMidToLow() {
    auto temp = midIDTree->minimum;
    lowIDTree->insert(temp->data);
    lowStrTree->insert(temp->data);
    midIDTree->remove(temp->getID());
    midStrTree->remove(temp->getID(),temp->getStrength());
}
void Team::moveHighToMid() {
    auto temp = highIDTree->minimum;
    midIDTree->insert(temp->data);
    midStrTree->insert(temp->data);
    highIDTree->remove(temp->getID());
    highStrTree->remove(temp->getID(),temp->getStrength());
}

void Team::moveLowToMid() {
    auto temp=lowIDTree->maximum;
    midIDTree->insert(temp->data);
    midStrTree->insert(temp->data);
    lowIDTree->remove(temp->getID());
    lowStrTree->remove(temp->getID(),temp->getStrength());
}

void Team::moveMidToHigh(){
    auto temp=midIDTree->maximum;
    highIDTree->insert(temp->data);
    highStrTree->insert(temp->data);
    midIDTree->remove(temp->getID());
    midStrTree->remove(temp->getID(),temp->getStrength());
}

void Team::moveLowToHigh() {
    moveLowToMid();
    moveMidToHigh();
}

void Team::moveHighToLow() {
    moveHighToMid();
    moveMidToLow();
}

void Team::redistribute() {
    int totalSize = contestants->getSize();
    int desiredSize = totalSize / 3;

    if (totalSize % 3 == 0) {
        //this function is O(log(n)) complexity because the excess in one subtree is at most 3 before we redistribute.
        //we call this only after insert and deletion.
        while (lowIDTree->getSize() != desiredSize || midIDTree->getSize() != desiredSize || highIDTree->getSize() != desiredSize) {
            // Address excess in highIDTree
            while (highIDTree->getSize() > desiredSize) {
                if (midIDTree->getSize() < desiredSize) {
                    moveHighToMid();
                } else {
                    moveHighToLow();
                }
            }

            // Address excess in midIDTree
            while (midIDTree->getSize() > desiredSize) {
                if (lowIDTree->getSize() < desiredSize) {
                    moveMidToLow();
                } else {
                    moveMidToHigh();
                }
            }

            // Address excess in lowIDTree
            while (lowIDTree->getSize() > desiredSize) {
                if (midIDTree->getSize() < desiredSize) {
                    moveLowToMid();
                } else {
                    moveLowToHigh();
                }
            }
        }
    }
}



void Team::updateStrength() {
    int sum = 0;
    sum += lowStrTree->getMaxStrength();
    sum += midStrTree->getMaxStrength();
    sum += highStrTree->getMaxStrength();
    strength = sum;
}


//returns true if Contestant can be inserted successfully into the team. Returns false otherwise.
//Maybe can clean this by making "findKthSmallest" just return the value instead of the node itself.
bool Team::addAux(shared_ptr<Contestant> contestant){


    if ((sport != contestant->getSport()) || (myCountry.lock()->getID() != contestant->getCountryID())) return false;
    //Check if contestant is not in maximum teams to enter a new team.
    if (!contestant->isAvailable() || contestant->isActiveInTeam(this->getID())) return false;
    // Check if contestant is already in team.
    if (!contestants->insert(contestant)) return false;
    contestant->addTeam(this->getID());

    strengths->insert(contestant);

    if (contestants->getSize() <= 1) {
        lowIDTree->insert(contestant);
        lowStrTree->insert(contestant);
    }
    // lowIDTree's maximum is nullptr, this gives out a seg-fault
    else if (lowIDTree->getSize() == 0 || contestant->getID() < lowIDTree->maximum->getID()){
        lowIDTree->insert(contestant);
        lowStrTree->insert(contestant);

    } else if(midIDTree->getSize() == 0 || (contestant->getID() < midIDTree->maximum->getID())){
        midIDTree->insert(contestant);
        midStrTree->insert(contestant);

    } else{
        highIDTree->insert(contestant);
        highStrTree->insert(contestant);
    }

    if (((contestants->getSize() % 3) == 0) && (contestants->getSize() > 0)){
        redistribute();
        updateStrength();
    }


    return true;
}
bool Team::addContestant(shared_ptr<Contestant> contestant) {
    if (!addAux(contestant)) return false;

    if ((contestants->getSize() % 3) == 0) updateAusMeasure();
    return true;
}
bool Team::removeContestant(int contestantID){
    if(!removeAux(contestantID)) return false;

    if ((contestants->getSize() % 3) == 0) updateAusMeasure();
    return true;
}

//returns true if contestant is in team. Returns false otherwise.
bool Team::removeAux(int contestantID) {
    auto currentContestant = contestants->find(contestantID);
    if (!currentContestant) return false;

    // redundant, already checked and handled error properly in Olympic's remove_contestant_from_team function
    currentContestant->removeTeam(this->getID());
    contestants->remove(contestantID);
    strengths->remove(contestantID,currentContestant->getStrength());

    // the removes do nothing if the contestant isn't the subtree. This just removes the contestant from whatever subtrees he's in
    // nice approach
    lowIDTree->remove(contestantID);
    lowStrTree->remove(contestantID,currentContestant->getStrength());
    midIDTree->remove(contestantID); //

    midStrTree->remove(contestantID,currentContestant->getStrength()); // this is incorrectly removing contestant 2 from the midStrTree
    highIDTree->remove(contestantID);

    highStrTree->remove(contestantID,currentContestant->getStrength()); // this is incorrectly removing contestant 3 from the highStrTree

    if (((contestants->getSize() % 3) == 0) && (contestants->getSize() > 0)){
        redistribute();
        updateStrength();
    }
    return true;

}



////Did a small change. Because before contestant removing himself from the team doesn't mean the team got updated. Seems fine.
//void Tea m: :  uniteTeamsIntoThis(shared_ptr<Team> otherTeam){
//
//    int numOfContestants = otherTeam->getNumberOfContestants();
//    shared_ptr<Contestant>* arr;
//    try {
//        arr = copyTeamIntoArrayAndUpdateContestants(otherTeam);
//    } catch (exception& e) {
//        throw e;
//    }
//    for (int i = 0; i < numOfContestants; i++) {
//        if (arr[i]->isActiveInTeam(this->getID())) continue;
//        addContestant(arr[i]);
//    }
//    delete[] arr;
//    //contestant->addTeam(shared_from_this()); //argument is method which converts the "this" pointer into shared_ptr
//}


//void Team::print(){
//    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
//    cout<<"Team ID: "<<getID()<<endl;
//    cout<<"PreOrder: [";
//    recursivePrintPreOrder(strengths->root);
//    cout<<"]"<<endl;
//    cout<<"InOrder: [";
//    recursivePrintInOrder(strengths->root);
//    cout<<"]"<<endl;
//    cout<<"Team strength: "<<getStrength()<<endl;
//    cout<<"Austerity measure(implemented now): "<<getAusMeasure()<<endl;
//    cout<<"Team Size: "<<strengths->getSize()<<endl;
//    cout<<"Sport: "<<(int)getSport()<<endl;
//    cout<<"Country ID: "<<getCountryID()<<endl;
//    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
//
//
//}

void Team::recursivePrintInOrder(shared_ptr<Node<Contestant>> node) {
    if (!node) return;
    recursivePrintInOrder(node->left);
    cout<<"("<<"str:"<<node->getStrength()<<", "<<"id: "<<node->getID()<<")";
    recursivePrintInOrder(node->right);
}


void Team::recursivePrintPreOrder(shared_ptr<Node<Contestant>> node) {
    if (!node) return;
    cout<<"("<<"str:"<<node->getStrength()<<", "<<"id: "<<node->getID()<<")";
    recursivePrintPreOrder(node->left);
    recursivePrintPreOrder(node->right);
}

int Team::getAusMeasure() const{
    if ( ( (contestants->getSize() - 3) > 0) && ((contestants->getSize() % 3) == 0) ) return ausMeasure;
    else return 0;
}

// We remove the minimums calculate and then reinsert, so we don't alter the tree for every scenario
// returns true if AusMeasure was updated 0 if not.

//Solution is "inefficient" but it is still O(log(n)). Other solutions are too complicated and require writing new logic.
//I prefer relying on our previous logic which is more tested and reliable. And the complexity is still O(log(n)) so it's fine.
bool Team::updateAusMeasure(){
    if ( ((contestants->getSize() % 3) != 0 ) || (contestants->getSize() == 0) ) return false;

    int initialStr = getStrength();
    int max = initialStr; //current strength

    //first scenario we remove the 3 weakest from the lower subtree.
    if (lowIDTree->getSize() >= 3){
        auto contestant1 = lowStrTree->minimum->data;// smallest
        removeAux(contestant1->getID());
        auto contestant2 = lowStrTree->minimum->data; //2nd smallest(because we removed the smallest so now 2nd smallest is the new smallest
        removeAux(contestant2->getID());
        auto contestant3 = lowStrTree->minimum->data;
        removeAux(contestant3->getID());
        max = getStrength() > max ? getStrength() : max; //calculating strength in this scenario

        //returning the contestants back to the team, so it remains ultimately unaltered.
        addAux(contestant1);
        addAux(contestant2);
        addAux(contestant3);
    }

    //exact same logic
    if (midIDTree->getSize() >= 3){
        auto contestant1 = midStrTree->minimum->data;// smallest
        removeAux(contestant1->getID());
        auto contestant2 = midStrTree->minimum->data; //2nd smallest(because we removed the smallest so now 2nd smallest is the new smallest
        removeAux(contestant2->getID());
        auto contestant3 = midStrTree->minimum->data;
        removeAux(contestant3->getID());
        max = getStrength() > max ? getStrength() : max;
        addAux(contestant1);
        addAux(contestant2);
        addAux(contestant3);
    }

    if (highIDTree->getSize() >= 3){
        auto contestant1 = highStrTree->minimum->data;// smallest
        removeAux(contestant1->getID());
        auto contestant2 = highStrTree->minimum->data; //2nd smallest(because we removed the smallest so now 2nd smallest is the new smallest
        removeAux(contestant2->getID());
        auto contestant3 = highStrTree->minimum->data;
        removeAux(contestant3->getID());
        max = getStrength() > max ? getStrength() : max;
        addAux(contestant1);
        addAux(contestant2);
        addAux(contestant3);
    }

    //Scenario 4: removing 2 weakest from lower and 1 from middle
    if (lowIDTree->getSize() >= 2 ){ //if lowIDTree has 2 contestants then midID should also have 2 because they're the same size before removal.
        auto contestant1 = lowStrTree->minimum->data;// smallest
        removeAux(contestant1->getID());
        auto contestant2 = lowStrTree->minimum->data; //2nd smallest(because we removed the smallest so now 2nd smallest is the new smallest
        removeAux(contestant2->getID());
        auto contestant3 = midStrTree->minimum->data;
        removeAux(contestant3->getID());
        max = getStrength() > max ? getStrength() : max;
        addAux(contestant1);
        addAux(contestant2);
        addAux(contestant3);
    }

    //Scenario 5: removing 2 weakest from lower and 1 from high
    if (lowIDTree->getSize() >= 2 ){ //if lowIDTree has 2 contestants then midID should also have 2 because they're the same size before removal.
        auto contestant1 = lowStrTree->minimum->data;// smallest
        removeAux(contestant1->getID());
        auto contestant2 = lowStrTree->minimum->data; //2nd smallest(because we removed the smallest so now 2nd smallest is the new smallest
        removeAux(contestant2->getID());
        auto contestant3 = highStrTree->minimum->data;
        removeAux(contestant3->getID());
        max = getStrength() > max ? getStrength() : max;
        addAux(contestant1);
        addAux(contestant2);
        addAux(contestant3);
    }

    //Scenario 6: removing 2 weakest from middle and 1 from low
    if (midIDTree->getSize() >= 2 ){ //if lowIDTree has 2 contestants then midID should also have 2 because they're the same size before removal.
        auto contestant1 = midStrTree->minimum->data;// smallest
        removeAux(contestant1->getID());
        auto contestant2 = midStrTree->minimum->data; //2nd smallest(because we removed the smallest so now 2nd smallest is the new smallest
        removeAux(contestant2->getID());
        auto contestant3 = lowStrTree->minimum->data;
        removeAux(contestant3->getID());
        max = getStrength() > max ? getStrength() : max;
        addAux(contestant1);
        addAux(contestant2);
        addAux(contestant3);
    }

    //Scenario 7: removing 2 weakest from middle and 1 from high
    if (midIDTree->getSize() >= 2 ){ //if lowIDTree has 2 contestants then midID should also have 2 because they're the same size before removal.
        auto contestant1 = midStrTree->minimum->data;// smallest
        removeAux(contestant1->getID());
        auto contestant2 = midStrTree->minimum->data; //2nd smallest(because we removed the smallest so now 2nd smallest is the new smallest
        removeAux(contestant2->getID());
        auto contestant3 = highStrTree->minimum->data;
        removeAux(contestant3->getID());
        max = getStrength() > max ? getStrength() : max;
        addAux(contestant1);
        addAux(contestant2);
        addAux(contestant3);
    }

    //Scenario 8: removing 2 weakest from high and 1 from low
    if (highIDTree->getSize() >= 2 ){ //if lowIDTree has 2 contestants then midID should also have 2 because they're the same size before removal.
        auto contestant1 = highStrTree->minimum->data;// smallest
        removeAux(contestant1->getID());
        auto contestant2 = highStrTree->minimum->data; //2nd smallest(because we removed the smallest so now 2nd smallest is the new smallest
        removeAux(contestant2->getID());
        auto contestant3 = lowStrTree->minimum->data;
        removeAux(contestant3->getID());
        max = getStrength() > max ? getStrength() : max;
        addAux(contestant1);
        addAux(contestant2);
        addAux(contestant3);
    }

    //Scenario 9: removing 2 weakest from high and 1 from mid
    if (highIDTree->getSize() >= 2 ){ //if lowIDTree has 2 contestants then midID should also have 2 because they're the same size before removal. And we only enter function if we're checking scenarios where size is divisible by 3
        auto contestant1 = highStrTree->minimum->data;// smallest
        removeAux(contestant1->getID());
        auto contestant2 = highStrTree->minimum->data; //2nd smallest(because we removed the smallest so now 2nd smallest is the new smallest
        removeAux(contestant2->getID());
        auto contestant3 = midStrTree->minimum->data;
        removeAux(contestant3->getID());
        max = getStrength() > max ? getStrength() : max;
        addAux(contestant1);
        addAux(contestant2);
        addAux(contestant3);
    }

    //Scenario 10: removing weakest from each
    if (lowIDTree->getSize() >= 1 ){
        auto contestant1 = lowStrTree->minimum->data;// smallest
        removeAux(contestant1->getID());
        auto contestant2 = midStrTree->minimum->data; //2nd smallest(because we removed the smallest so now 2nd smallest is the new smallest
        removeAux(contestant2->getID());
        auto contestant3 = highStrTree->minimum->data;
        removeAux(contestant3->getID());
        max = getStrength() > max ? getStrength() : max;
        addAux(contestant1);
        addAux(contestant2);
        addAux(contestant3);
    }


    ausMeasure = max;
    return (initialStr != max);
}


shared_ptr<Contestant>* Team::copyTeamIntoArrayAndUpdateContestants(shared_ptr<Team> team) {
    int numOfContestants = team->getNumberOfContestants();
    shared_ptr<Contestant>* arr;
    arr = new shared_ptr<Contestant>[numOfContestants];
    int i=0;
    auxCopy(team->contestants->root, arr, i, team);
    return arr;
}

void Team::auxCopy(shared_ptr<Node<Contestant>> root, shared_ptr<Contestant>* arr, int& index, shared_ptr<Team> team) {
    if (!root || !team || !arr) return;

    root->data->removeTeam(team->getID());
    if (root->left) auxCopy(root->left, arr, index, team);
    arr[index++] = root->data;
    if (root->right) auxCopy(root->right, arr, index, team);
}

void Team::uniteWith(shared_ptr<Team> other) {
    auto fullIDArr1 = this->contestants->returnSortedArrayOfElements();
   //this function which I implemented before updates the contestants that they're no longer part of a team during copy.
   //we need to do this once so the contestants know they're no longer part of the other team.
    auto fullIDArr2 = copyTeamIntoArrayAndUpdateContestants(other);
    int totalIDSize;
    auto mergedIDArr = mergeIDArrays(fullIDArr1, fullIDArr2,this->contestants->size,other->contestants->size, &totalIDSize);
    auto fullStrArr1 = this->strengths->returnSortedArrayOfElements();
    auto fullStrArr2 = other->strengths->returnSortedArrayOfElements();
    int totalStrSize;
    auto mergedStrArr = mergeStrArrays(fullStrArr1,fullStrArr2,this->strengths->size, other->strengths->size, &totalStrSize);

    int mergedLowIDSize = (totalIDSize / 3) + (((totalIDSize % 3) >=1 ) ? 1 : 0);
    int mergedMidIDSize = (totalIDSize / 3) + (((totalIDSize % 3) == 2 ) ? 1 : 0);
    int mergedHighIDSize = totalIDSize / 3;

    this->contestants = make_shared<Tree<Contestant>>(mergedIDArr, totalIDSize);
    this->strengths = make_shared<STree<Contestant>>(mergedStrArr, totalStrSize);
    this->lowIDTree = make_shared<Tree<Contestant>>(mergedIDArr, mergedLowIDSize);
    this->midIDTree = make_shared<Tree<Contestant>>(mergedIDArr+mergedLowIDSize, mergedMidIDSize);
    this->highIDTree = make_shared<Tree<Contestant>>(mergedIDArr+mergedLowIDSize+mergedMidIDSize, mergedHighIDSize);

    auto mergedLowStr = new shared_ptr<Contestant>[mergedLowIDSize];
    auto mergedMidStr = new shared_ptr<Contestant>[mergedMidIDSize];
    auto mergedHighStr = new shared_ptr<Contestant>[mergedHighIDSize];


    int l = 0, m = 0, h = 0;
    for (int i = 0; i < totalStrSize; i++) {
        //update new contestants that they joined the team.
        if (!mergedStrArr[i]->isActiveInTeam(this->getID())) mergedStrArr[i]->addTeam(this->getID());

        if (mergedStrArr[i]->getID() <= lowIDTree->maximum->getID()) {
            mergedLowStr[l] = mergedStrArr[i];
            l++;
        }
        else if (mergedStrArr[i]->getID() <= midIDTree->maximum->getID()) {
            mergedMidStr[m] = mergedStrArr[i];
            m++;
        }
        else {
            mergedHighStr[h] = mergedStrArr[i];
            h++;
        }
    }

    this->lowStrTree = make_shared<STree<Contestant>>(mergedLowStr, mergedLowIDSize);
    this->midStrTree = make_shared<STree<Contestant>>(mergedMidStr, mergedMidIDSize);
    this->highStrTree = make_shared<STree<Contestant>>(mergedHighStr, mergedHighIDSize);

    this->updateStrength();
    this->updateAusMeasure();
    this->redistribute();

    delete[] fullIDArr1;
    delete[] fullIDArr2;
    delete[] fullStrArr1;
    delete[] fullStrArr2;
    delete[] mergedStrArr;
    delete[] mergedIDArr;
    delete[] mergedLowStr;
    delete[] mergedMidStr;
    delete[] mergedHighStr;


}

shared_ptr<Contestant>* Team::mergeIDArrays(shared_ptr<Contestant>* arr1, shared_ptr<Contestant>* arr2, int size1, int size2, int* totalSize) {
    *totalSize = size1 + size2;
    shared_ptr<Contestant>* result = new std::shared_ptr<Contestant> [*totalSize];

    int i = 0, j = 0, k = 0;
    shared_ptr<Contestant> lastAdded = nullptr;

    while (i < size1 && j < size2) {
        if (arr1[i]->getID() < arr2[j]->getID()) {
            if (!lastAdded || arr1[i]->getID() != lastAdded->getID()) {
                lastAdded = arr1[i];
                result[k++] = arr1[i];
            }
            i++;
        } else if (arr1[i]->getID() > arr2[j]->getID()) {
            if (!lastAdded || arr2[j]->getID() != lastAdded->getID()) {
                lastAdded = arr2[j];
                result[k++] = arr2[j];
            }
            j++;
        } else {
            if (!lastAdded || arr1[i]->getID() != lastAdded->getID()) {
                lastAdded = arr1[i];
                result[k++] = arr1[i];
            }
            i++;
            j++;
        }
    }

    while (i < size1) {
        if (!lastAdded || arr1[i]->getID() != lastAdded->getID()) {
            lastAdded = arr1[i];
            result[k++] = arr1[i];
        }
        i++;
    }

    while (j < size2) {
        if (!lastAdded || arr2[j]->getID() != lastAdded->getID()) {
            lastAdded = arr2[j];
            result[k++] = arr2[j];
        }
        j++;
    }

    *totalSize = k;
    return result;
}


shared_ptr<Contestant>* Team::mergeStrArrays(shared_ptr<Contestant>* arr1, shared_ptr<Contestant>* arr2, int size1, int size2, int* totalSize) {
    *totalSize = size1 + size2;
    shared_ptr<Contestant>* result = new shared_ptr<Contestant>[*totalSize];

    int i = 0, j = 0, k = 0; // Indices for arr1, arr2, and result
    shared_ptr<Contestant> lastAdded = nullptr;

    while (i < size1 && j < size2) {
        if (arr1[i]->getStrength() < arr2[j]->getStrength() ||
            (arr1[i]->getStrength() == arr2[j]->getStrength() && arr1[i]->getID() < arr2[j]->getID())) {
            if (!lastAdded || arr1[i]->getID() != lastAdded->getID()) {
                lastAdded = arr1[i];
                result[k++] = arr1[i];
            }
            i++;
        } else if (arr1[i]->getStrength() > arr2[j]->getStrength() ||
                   (arr1[i]->getStrength() == arr2[j]->getStrength() && arr1[i]->getID() > arr2[j]->getID())) {
            if (!lastAdded || arr2[j]->getID() != lastAdded->getID()) {
                lastAdded = arr2[j];
                result[k++] = arr2[j];
            }
            j++;
        } else { // When strengths are equal and IDs are equal, skip one
            if (!lastAdded || arr1[i]->getID() != lastAdded->getID()) {
                lastAdded = arr1[i];
                result[k++] = arr1[i];
            }
            i++; j++;
        }
    }

    while (i < size1) {
        if (!lastAdded || arr1[i]->getID() != lastAdded->getID()) {
            lastAdded = arr1[i];
            result[k++] = arr1[i];
        }
        i++;
    }

    while (j < size2) {
        if (!lastAdded || arr2[j]->getID() != lastAdded->getID()) {
            lastAdded = arr2[j];
            result[k++] = arr2[j];
        }
        j++;
    }

    *totalSize = k;
    return result;
}