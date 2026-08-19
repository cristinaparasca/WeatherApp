#ifndef COUNTY_H
#define COUNTY_H
#include <QString>
#include <QStringList>
using namespace std;
#include <iostream>

struct County{
    QString name;
    QStringList cities;
    County()=default;
    County(const QString& _name,const QStringList& _cities):name{_name},cities{_cities}{};
    bool operator==(const County& other) const
    {
        return other.name==this->name && other.cities==this->cities;
    }

    bool operator!=(const County& other) const
    {
        return other.name!=this->name || other.cities!=this->cities;
    }
// GCOVR_EXCL_START
    friend std::ostream& operator<<(std::ostream &out,const County& county)
    {
        out<<"County -> name:'"<<(county.name).toStdString()<<"', cities:[";
        int citiesSize=county.cities.size();
        for(int i=0;i<citiesSize-1;i++)
        {
            out<<"'"<<county.cities[i].toStdString()<<"', ";
        }
        out<<"'"<<county.cities[citiesSize-1].toStdString()<<"']";

        return out;
    }
    // GCOVR_EXCL_STOP
};

#endif // COUNTY_H
