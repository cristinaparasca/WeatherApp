#include <boost/test/unit_test.hpp>
#include <includes/countriesmodel.h>
#include <boost/test/tools/detail/print_helper.hpp>

namespace boost::test_tools::tt_detail
{
template<>
struct print_log_value<QString>
{
    void operator()(std::ostream& os, const QString& value)
    {
        os << value.toStdString();
    }
};
}

struct CountyFixture
{
    CountyFixture()
        : data{
            {"Alba", {"Alba Iulia", "Blaj"}},
            {"Arad", {"Ineu", "Lipova"}},
            {"Argeș", {"Pitești", "Câmpulung", "Mioveni"}}
        }
    {
    }

    QVector<County> data;
};

BOOST_AUTO_TEST_SUITE(CountiesModelTests)

BOOST_AUTO_TEST_CASE(defaultConstructor_rowCountIsZero)
{
    CountiesModel countiesModel;

    BOOST_TEST(countiesModel.rowCount(QModelIndex())==0);
}

BOOST_FIXTURE_TEST_CASE(update_updatesRowCount,CountyFixture)
{
    CountiesModel countiesModel;
    countiesModel.update(std::move(data));
    BOOST_TEST(countiesModel.rowCount(QModelIndex())==3);
}

BOOST_FIXTURE_TEST_CASE(update_returnsExpectedCountyName,CountyFixture)
{
    CountiesModel countiesModel;
    countiesModel.update(std::move(data));
    QString expectedCountyName{"Alba"};
    QModelIndex idx=countiesModel.index(0,0);
    QVariant returnedCountyName=countiesModel.data(idx,CountiesModel::NameRole);
    BOOST_CHECK_EQUAL(expectedCountyName,returnedCountyName.toString());
}

BOOST_FIXTURE_TEST_CASE(data_returnsExpectedCities,CountyFixture)
{

    CountiesModel countiesModel;
    countiesModel.update(std::move(data));
    QStringList expectedCities={"Alba Iulia","Blaj"};

    QModelIndex idx=countiesModel.index(0,0);
    QVariant returnedCities=countiesModel.data(idx,CountiesModel::CitiesRole);
    QStringList returnedCitiesQStringList=returnedCities.toStringList();
    BOOST_CHECK_EQUAL_COLLECTIONS(returnedCitiesQStringList.begin(),returnedCitiesQStringList.end(),
                                    expectedCities.begin(),expectedCities.end());
}

BOOST_FIXTURE_TEST_CASE(roleNames_returnsExpectedRoles,CountyFixture)
{
    CountiesModel countiesModel;
    countiesModel.update(std::move(data));
    QHash<int, QByteArray> expectedRoleNames{{CountiesModel::NameRole,"name"},{CountiesModel::CitiesRole,"cities"}};
    BOOST_TEST(countiesModel.roleNames()==expectedRoleNames);
}

BOOST_FIXTURE_TEST_CASE(update_replacesOldData,CountyFixture)
{
    CountiesModel countiesModel;
    //first update
    countiesModel.update(std::move(data));
    QStringList expectedCities={"Alba Iulia","Blaj"};

    //second update
    QVector<County> data2={
        {"Bacău",{"Bacău","Onești","Moinești","Comănești"}}
    };
    countiesModel.update(std::move(data2));

    //check new RowCount
    QModelIndex idx=countiesModel.index(0,0);
    BOOST_TEST(countiesModel.rowCount(QModelIndex())==1);

    //check County Name
    QString expectedCountyName{"Bacău"};
    QVariant returnedCountyName=countiesModel.data(idx,CountiesModel::NameRole);
    BOOST_CHECK_EQUAL(expectedCountyName,returnedCountyName.toString());
}

BOOST_FIXTURE_TEST_CASE(data_invalidIndexReturnsInvalidVariant,CountyFixture)
{
    CountiesModel countiesModel;
    //first update
    countiesModel.update(std::move(data));

    QModelIndex idx=countiesModel.index(-1,0);

    QVariant returnedCountyName=countiesModel.data(idx,CountiesModel::NameRole);

    BOOST_TEST(!returnedCountyName.isValid());
}

BOOST_AUTO_TEST_CASE(data_emptyDataReturnsInvalidVariant)
{
    CountiesModel countiesModel;

    QModelIndex idx=countiesModel.index(0,0);

    QVariant returnedCountyName=countiesModel.data(idx,CountiesModel::NameRole);

    BOOST_TEST(!returnedCountyName.isValid());
}

BOOST_FIXTURE_TEST_CASE(data_invalidRoleReturnsInvalidVariant,CountyFixture)
{

    CountiesModel countiesModel;
    //first update
    countiesModel.update(std::move(data));

    QModelIndex idx=countiesModel.index(0,0);

    QVariant returnedCountyName=countiesModel.data(idx,Qt::UserRole);

    BOOST_TEST(!returnedCountyName.isValid());
}

BOOST_AUTO_TEST_SUITE_END()

