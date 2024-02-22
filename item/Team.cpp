//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"



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

            // Address deficit in lowIDTree by moving from mid or high
            while (lowIDTree->getSize() < desiredSize) {
                if (midIDTree->getSize() > desiredSize) {
                    moveMidToLow();
                } else if (highIDTree->getSize() > desiredSize) {
                    moveHighToLow();
                }
            }
        }
    }
}



void Team::updateStrength() {
    int sum = 0;
    sum += lowStrTree->getMax()->getStrength();
    sum += midStrTree->getMax()->getStrength();
    sum += highStrTree->getMax()->getStrength();
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
//    contestant->addTeam(shared_from_this()); //argument is method which converts the "this" pointer into shared_ptr


    shared_ptr<Node<Contestant>> lowSNode, midSNode;

    strengths->insert(contestant);
        lowSNode  = contestants->findKthSmallest(contestants->root,contestants->getSize()/3);
        midSNode = contestants->findKthSmallest(contestants->root,(contestants->getSize() * 2)/3);


    if (contestants->getSize() <= 1) {
        lowIDTree->insert(contestant);
        lowStrTree->insert(contestant);
    }

    else if (contestant->getID() < lowSNode->getID()){
        lowIDTree->insert(contestant);
        lowStrTree->insert(contestant);

    } else if(contestant->getID() < midSNode->getID()){
        midIDTree->insert(contestant);
        midStrTree->insert(contestant);

    } else{
        highIDTree->insert(contestant);
        highStrTree->insert(contestant);
    }

    if (((contestants->getSize() % 3) == 0) && (contestants->getSize() > 0)){
//        redistribute(); commented out for compilation reasons
//        updateStrength();
//        updateAusMeasure();
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
    midIDTree->remove(contestantID);
    midStrTree->remove(contestantID,currentContestant->getStrength());
    highIDTree->remove(contestantID);
    highStrTree->remove(contestantID,currentContestant->getStrength());

//    redistribute(); commented out for compilation reasons
//    updateStrength();
//    updateAusMeasure();
    return true;

}




void Team::uniteAux(shared_ptr<Node<Contestant>> root, int teamId){
    if(!root) return;
    auto contestant = root->data;
    contestant->removeTeam(teamId); // important in order to make sure that the contestant can join a new team.
    addContestant(root->data);
    contestant->addTeam(shared_from_this()); //argument is method which converts the "this" pointer into shared_ptr

    uniteAux(root->left, teamId);
    uniteAux(root->right, teamId);
}

void Team::uniteWith(shared_ptr<Team> other) {
    uniteAux(other->contestants->root, other->getID());
}


