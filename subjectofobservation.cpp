#include "subjectofobservation.h"

void SubjectOfObservation::attach(Observer *obs) {
    this->myObservers.insert(obs);
}

void SubjectOfObservation::detach(Observer *obs) {
    this->myObservers.erase(obs);
}

void SubjectOfObservation::notify() {
    for (std::set<Observer*>::iterator it=this->myObservers.begin(); it!=this->myObservers.end(); ++it)
        (*it)->refresh(this);
}
