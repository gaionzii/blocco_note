/* Classi che rappresentano note (es. Bear / Evernote).
Ogni nota è composta da titolo e testo, può essere bloccata per evitarne cancellazione/modifica e fa parte di una collezione
specificata con nome. Può anche far parte di una collezione di note importanti oltre che di una collezione specifica. Usare
Observer per indicare quante note stanno in una collezione. */

#include <iostream>
#include <string>
#include <list>
using namespace std;

class Observer {
public:
    ~Observer() {};
    virtual void update(bool a, const string& s) = 0;
};

class Subject {
private:
    list<Observer*> obs;
public:
    virtual ~Subject() {};
    virtual void addObserver(Observer* o)=0;
    virtual void removeObserver(Observer* o)=0;
    virtual void notifyObserver(bool a, const string& s)=0;
};

class Nota {
private:
    string titolo;
    string testo;
    bool bloccata;
    string NomeCollezione;
    bool importante;
public:
    Nota (const string& t, const string& te, string n): titolo(t), testo(te), bloccata(false), NomeCollezione(n), importante(false){};
    ~Nota(){};

    void blocca(){bloccata=true;};
    void sblocca(){bloccata=false;};
    void setTitolo(string t){
        if (bloccata==true)
            cout<<"la nota è bloccata, il suo titolo non è modificabile"<<endl;
        else
            titolo=t;
    }
    void setTesto(string t){
        if (bloccata==true)
            cout<<"la nota è bloccata, il suo testo non è modificabile"<<endl;
        else
            testo=t;
    }
    bool getBloccata(){return bloccata;}
};

class Collezione: public Subject{
private:
    list<Nota*> note;
    list<Observer*> obs;
protected:
    string nome;
public:
    Collezione(const string& n): nome(n){};
    ~Collezione(){};
    void addNota(Nota* n){
        note.push_back(n);
        bool a=true;
        notifyObserver(a, nome);
    }
    void removeNota(Nota* n){
        if (n->getBloccata()==true)
            cout<<"la nota è bloccata, non può essere cancellata";
        else {
            note.remove(n);
            bool a=false;
            notifyObserver(a, nome);
        }
    }

    virtual void addObserver(Observer* o) override{obs.push_back(o);};
    virtual void removeObserver(Observer* o) override{obs.remove(o);};
    virtual void notifyObserver(bool a, const string& s) override{
        for(auto i: obs){
            i->update(a, s);
        }
    }

};

class Counter: public Observer {
private:
    int count;
    Collezione* c;
public:
    Counter(Collezione* co): count(0), c(co){
        c->addObserver(this);
    };
    ~Counter(){
        c->removeObserver(this);
    };
    void update(bool a, const string& s) override{
        // da implementare
    }

};