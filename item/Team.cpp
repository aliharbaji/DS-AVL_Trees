//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"
#include <iostream>



//int Team::getMedals() const {
//    return medals;
//}

int Team::getStrength() const {
    int value = ((getNumberOfContestants() % 3) == 0) ? strength : 0;
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
        //this function is O(logn) complexity because the excess in one subtree is at most 3 before we redistribute.
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
bool Team::addContestant(shared_ptr<Contestant> contestant){

    // redundant, will make sure to check these in Olympic's add_contestant_to_team function for a cleaner code.
    // it wouldn't hurt to keep as is, will not change that in the time being
    // check if contestant has same sport and country as team
    if ((sport != contestant->getSport()) || (myCountry.lock()->getID() != contestant->getCountryID())) return false;
    //Check if contestant is not in maximum teams to enter a new team.
    if (!contestant->isAvailable()) return false;
    // Check if contestant is already in team.
    if (!contestants->insert(contestant)) return false;
    contestant->addTeam(this->getID());

    strengths->insert(contestant);

    if (contestants->getSize() <= 1) {
        lowIDTree->insert(contestant);
        lowStrTree->insert(contestant);
    }
    else if (contestant->getID() < lowIDTree->maximum->getID()){
        lowIDTree->insert(contestant);
        lowStrTree->insert(contestant);

    } else if(midIDTree->getSize() == 0 ||(contestant->getID() < midIDTree->maximum->getID())){
        midIDTree->insert(contestant);
        midStrTree->insert(contestant);

    } else{
        highIDTree->insert(contestant);
        highStrTree->insert(contestant);
    }

    if (((contestants->getSize() % 3) == 0) && (contestants->getSize() > 0)){
        redistribute();
        updateStrength();
        updateAusMeasure();
    }


    return true;
}

//returns true if contestant is in team. Returns false otherwise.
bool Team::removeContestant(int contestantID) {
    auto currentContestant = contestants->find(contestantID);
    if (!currentContestant) return false;

    // redundant, already checked and handled error properly in Olympic's remove_contestant_from_team function
    if (!currentContestant->removeTeam(this->getID())) throw logic_error("contestant in team but doesn't know it");
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

    redistribute();
    updateStrength();
    updateAusMeasure();
    return true;

}



//Did a small change. Because before contestant removing himself from the team doesn't mean the team got updated. Seems fine.
void Team::uniteAux(shared_ptr<Node<Contestant>> root, shared_ptr<Team> team){
    if(!root) return;

    auto contestant = root->data;

    // check if contestant is already in the team
    bool contestantIsAlreadyInTargetTeam = contestant->isActiveInTeam(this->getID()); // this takes O(1) time

    // unite other contestants with the target team
    uniteAux(root->left, team);
    uniteAux(root->right, team);

    if(contestantIsAlreadyInTargetTeam){
        team->removeContestant(contestant->getID());
        return;
    }
    // if the contestant is already in target team, we don't want to add him again so this part of the code becomes unreachable


    team->removeContestant(contestant->getID()); // important in order to make sure that the contestant can join a new team.
    addContestant(root->data);
    //contestant->addTeam(shared_from_this()); //argument is method which converts the "this" pointer into shared_ptr
}

void Team::uniteWith(shared_ptr<Team> other) {
    uniteAux(other->contestants->root, other);
}

void Team::print(){
    if(this == nullptr) return;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"Team ID: "<<getID()<<endl;
    cout<<"PreOrder: [";
    recursivePrintPreOrder(strengths->root);
    cout<<"]"<<endl;
    cout<<"InOrder: [";
    recursivePrintInOrder(strengths->root);
    cout<<"]"<<endl;
    cout<<"Team strength: "<<getStrength()<<endl;
    cout<<"Austerity measure(not implemented yet): "<<getAusMeasure()<<endl;
    cout<<"Team Size: "<<strengths->getSize()<<endl;
    cout<<"Sport: "<<(int)getSport()<<endl;
    cout<<"Country ID: "<<getCountryID()<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;


}

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

// need implementation
int Team::getAusMeasure() const{
    if ((contestants->size % 3) != 0) return 0;

    int max=0;
    if (lowIDTree->size >= 3) {
        int hypoStr3Low; //hypothetical strength 3 low. Meaning what would the strength be if we removed the 3 weakest people from low subtree.

    }
}

void Team::updateAusMeasure(){

}

