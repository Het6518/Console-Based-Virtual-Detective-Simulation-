#include <bits/stdc++.h>
using namespace std;

class Character {
public:
    virtual void getDetails() const = 0;
    virtual ~Character() = default;
};

class Suspect : public Character {
protected:
    string name;
    string alibi;
    bool hasAccess;
    int suspicion = 0;

public:
    Suspect(string n, string a, bool access)
        : name(n), alibi(a), hasAccess(access) {}

    void getDetails() const override {
        cout << "Suspect: " << name << "\n";
    }

    void revealAlibi() const {
        cout << name << ": " << alibi << "\n";
    }

    bool accessGranted() const { return hasAccess; }

    void increaseSuspicion(int val) { suspicion += val; }

    int getSuspicion() const { return suspicion; }

    string getName() const { return name; }
};

class Thief : public Suspect {
public:
    Thief(string a, bool access)
        : Suspect("Thief", a, access) {}
};

class Hacker : public Suspect {
public:
    Hacker(string a, bool access)
        : Suspect("Hacker", a, access) {}
};

class Businessman : public Suspect {
public:
    Businessman(string a, bool access)
        : Suspect("Businessman", a, access) {}
};

class Detective : public Character {
public:
    virtual void investigate(Suspect& s) = 0;
};

class LogicalDetective : public Detective {
public:
    void getDetails() const override {
        cout << "Detective: Logical Detective\n";
    }

    void investigate(Suspect& s) override {
        cout << "\nInvestigating " << s.getName() << "...\n";
        s.revealAlibi();

        if (s.accessGranted()) {
            cout << "Had access\n";
            s.increaseSuspicion(2);
        } else {
            cout << "No access\n";
            s.increaseSuspicion(-1);
        }
    }
};

struct CaseFile {
    string description;
    vector<unique_ptr<Suspect>> suspects;
};

vector<CaseFile> createCases() {
    vector<CaseFile> cases;

    {
        CaseFile c;
        c.description = "A businessman was found dead in his office at 9 PM. No forced entry.";
        c.suspects.push_back(make_unique<Thief>("I was stealing at the market. CCTV confirms.", false));
        c.suspects.push_back(make_unique<Hacker>("I was home fixing servers. No witnesses.", true));
        c.suspects.push_back(make_unique<Businessman>("I was attending a party with guests.", false));
        cases.push_back(move(c));
    }

    {
        CaseFile c;
        c.description = "A hacker was poisoned at a tech conference. Poison was mixed in coffee.";
        c.suspects.push_back(make_unique<Thief>("I never drink coffee. Only energy drinks.", false));
        c.suspects.push_back(make_unique<Hacker>("I was on stage during the break.", false));
        c.suspects.push_back(make_unique<Businessman>("I personally handed him the coffee.", true));
        cases.push_back(move(c));
    }

    {
        CaseFile c;
        c.description = "A thief was shot in a dark alley at midnight. A gun was found nearby.";
        c.suspects.push_back(make_unique<Thief>("I was hiding stolen goods elsewhere.", false));
        c.suspects.push_back(make_unique<Hacker>("I was coding all night. No witnesses.", false));
        c.suspects.push_back(make_unique<Businessman>("I own a licensed gun for protection.", true));
        cases.push_back(move(c));
    }

    {
        CaseFile c;
        c.description = "A wealthy businessman was kidnapped from a parking lot at 7 PM.";
        c.suspects.push_back(make_unique<Thief>("I was pickpocketing at the station.", false));
        c.suspects.push_back(make_unique<Hacker>("I disabled CCTV cameras at 6:55 PM.", true));
        c.suspects.push_back(make_unique<Businessman>("I was closing a deal in another city.", false));
        cases.push_back(move(c));
    }

    {
        CaseFile c;
        c.description = "A hacker was electrocuted in his lab. Only authorized staff had access.";
        c.suspects.push_back(make_unique<Thief>("I don’t understand electronics at all.", false));
        c.suspects.push_back(make_unique<Hacker>("I had full lab access, but he was my friend.", true));
        c.suspects.push_back(make_unique<Businessman>("I was stuck in traffic for hours.", false));
        cases.push_back(move(c));
    }

    return cases;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(time(nullptr));

    vector<CaseFile> cases = createCases();
    CaseFile& caseFile = cases[rand() % cases.size()];

    LogicalDetective detective;

    cout << "VIRTUAL DETECTIVE GAME\n\n";
    cout << "CASE:\n" << caseFile.description << "\n";

    for (auto& suspect : caseFile.suspects) {
        detective.investigate(*suspect);
    }

    auto culprit = max_element(
        caseFile.suspects.begin(),
        caseFile.suspects.end(),
        [](const auto& a, const auto& b) {
            return a->getSuspicion() < b->getSuspicion();
        });

    cout << "\nMost suspicious suspect: " << (*culprit)->getName() << "\n";

    return 0;
}
