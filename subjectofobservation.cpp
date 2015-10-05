#include "subjectofobservation.h"

SubjectOfObservation::SubjectOfObservation() {}

SubjectOfObservation::~SubjectOfObservation() {}

SubjectOfObservation::attach(Observer *obs) {
    this->myObservers.insert(obs);
}

SubjectOfObservation::detach(Observer *obs) {
    this->myObservers.erase(obs);
}

SubjectOfObservation::notify() {
    for (std::set<Observer*>::iterator it=this->myObservers.begin(); it!=this->myObservers.end(); ++it)
        (*it)->refresh(this);
}
