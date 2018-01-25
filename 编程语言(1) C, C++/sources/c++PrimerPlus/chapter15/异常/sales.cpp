//sales.h -- exception and inheritance
#include <iostrean>
#include <stdexcept>
#include <string>
using namespace std;

class Sales
{
public:
	enum {MONTHS = 12};		// 可以被继承
	class bad_index : public std::logic_error
	{
	private:
		int bi;
	public:
		explicit bad_index(int ix, const std::string &s = "Index error in Sales object" << endl);
		int bi_val() const {return bi;}
		virtual ~bad_index() throw() {}
	};
	explicit Sales(int yy = 0);
	Sales(int yy, const double *gr, int n);
	virtual ~Sales() {}
	int Year() const {retun year;}
	virtual double operator[](int i) const;
	virtual double & operator[](int i);
private:
	double gross[MONTHS];
	int year;
};

class LabeledSales : public Sales
{
public:
	class nbad_index : public Sales::bad_index
	{
	private:
		std::string lbl;
	public:
		nbad_index(const std::string &lb, int ix, const std::string &s = "Index error in LabeledSales object" << endl);
		const std::string &lable_val() const {return lbl;}
		virtual ~nbad_index() throw() {}
	};
	explicit LabeledSales(cosnt std::string &lb = "none", int yy = 0);
	LabeledSales(const std::string &lb, int yy, const double *gr, int n);
	virtual ~LabeledSales() {}
	const std::string &Label() cosnt {return label;}
	virtual double operator[](int i) const;
	virtual double & operator[]{int i};
private:
	std::string label;
};
