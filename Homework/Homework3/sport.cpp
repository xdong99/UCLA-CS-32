class Sport
{
public:
    Sport(string name){m_string = name;}
    virtual ~Sport(){};
    
    virtual string name() const {return m_string;}
    virtual bool isOutdoor() const {return true;}
    virtual string icon() const = 0;
    
private:
    string m_string;
};

class Snowboarding : public Sport
{
public:
    Snowboarding(string name);
    virtual ~Snowboarding();
    virtual string icon() const;
};

Snowboarding::Snowboarding(string name)
:Sport(name)
{}

Snowboarding::~Snowboarding()
{
    cout << "Destroying the Snowboarding object named " << name() << "." << endl;
}

string Snowboarding::icon() const
{
    return "a descending snowboarder";
}


class Biathlon : public Sport
{
public:
    Biathlon(string name, double distance);
    virtual ~Biathlon();
    virtual double getDistance() {return m_distance;}
    virtual string icon() const;
private:
    double m_distance;
};

Biathlon::Biathlon(string name, double distance)
:Sport(name), m_distance(distance)
{}

Biathlon::~Biathlon()
{
    cout << "Destroying the Biathlon object named " << name() << ", distance " << getDistance() << " km." << endl;
}

string Biathlon::icon() const
{
    return "a skier with a rifle";
}

class FigureSkating : public Sport
{
public:
    FigureSkating(string name);
    virtual ~FigureSkating();
    virtual bool isOutdoor() const;
    virtual string icon() const;
};

FigureSkating::FigureSkating(string name)
:Sport(name)
{}

FigureSkating::~FigureSkating()
{
    cout << "Destroying the FigureSkating object named " << name() << "." << endl;
}

bool FigureSkating::isOutdoor() const
{
    return false;
}

string FigureSkating::icon() const
{
    return "a skater in the Biellmann position";
}
