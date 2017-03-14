#include <iostream>
using namespace std;
 
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#endif
class Fraction
{
    int _numerator;
    int _denominator;
    // 由double赋值时的精度阈值
    static const double threshold;
    // 化简
    void simplify()
    {
        if(_denominator < 0)
        {
            _denominator = -_denominator;
            _numerator = -_numerator;
        }
        if(_numerator)
        {
            int Mxfactor;
            Mxfactor = MaxCommFactor(_numerator, _denominator);
            _numerator /= Mxfactor;
            _denominator /= Mxfactor;
        }
    };
public:
    // 构造
    Fraction() : _numerator(0), _denominator(1){};
    Fraction(int n, int den = 1) :
        _numerator(n), _denominator(den)
    {
        simplify();
    };
    Fraction(double frac)
    {
        if(frac < 0)
        {
            frac = -frac;
            _numerator = -1;
        }
        else
            _numerator = 1;
        int i = 1;
        double delta;
        do
        {
            i++;
            delta = frac*i;
            delta -= (int)delta;
        } while(delta > threshold);
        _numerator *= (int)(frac*i);
        _denominator = i;
    }
    // 取得分子分母
    int GetNumer() const { return _numerator; };
    int GetDenoMina() const { return _denominator; };
    // 复制
    Fraction* Copy() const
    {
        Fraction*  frac = new Fraction;
        frac->_numerator = _numerator;
        frac->_denominator = _denominator;
        return frac;
    }
    void CopyTo(Fraction* frac) const
    {
        frac->_numerator = _numerator;
        frac->_denominator = _denominator;
    }
    // 取倒数
    Fraction& Reciprocal()
    {
        int temp = _denominator;
        _denominator = _numerator;
        _numerator = temp;
        if(_denominator < 0)
        {
            _denominator = -_denominator;
            _numerator = -_numerator;
        }
        return *this;
    }
    // 转换成double操作符
    operator double() const
    {
        return _numerator / (double)_denominator;
    }
    // 负号操作符
    Fraction operator-() const
    {
        Fraction frac(*this);
        frac._numerator = -_numerator;
        return frac;
    }
    // 加法操作符
    Fraction operator+ (const Fraction& frac) const
    {
        int MinMulti = MinCommMulti(_denominator, frac._denominator);
        return Fraction(_numerator*MinMulti / _denominator + frac._numerator*MinMulti / frac._denominator, MinMulti);
    }
    Fraction operator+ (double frac) const
    {
        return Fraction((double)*this + frac);
    }
    friend Fraction operator+(double a, const Fraction& b);
    // 减法操作符
    Fraction operator- (const Fraction& frac) const
    {
        return -frac + *this;
    }
    Fraction operator- (double frac) const
    {
        return -frac + *this;
    }
    friend Fraction operator-(double a, const Fraction& b);
    // 乘法操作符
    Fraction operator*(const Fraction& frac) const
    {
        return Fraction(_numerator*frac._numerator, _denominator*frac._denominator);
    }
    Fraction operator*(double frac) const
    {
        return Fraction((double)*this*frac);
    }
    friend Fraction operator*(double a, const Fraction& b);
    // 除法操作符
    Fraction operator/(const Fraction& frac) const
    {
        return Fraction(_numerator*frac._denominator, _denominator*frac._numerator);
    }
    Fraction operator/(double frac) const
    {
        return Fraction((double)*this / frac);
    }
    friend Fraction operator/(double a, const Fraction& b);
    // 赋值操作符
    Fraction& operator= (const Fraction& frac)
    {
        _numerator = frac._numerator;
        _denominator = frac._denominator;
        return *this;
    }
    Fraction& operator= (double frac)
    {
        return operator= (Fraction(frac));
    }
    // ==&&!=
    bool operator== (const Fraction& frac) const
    {
        return _numerator == frac._numerator&&_denominator == frac._denominator;
    }
    bool operator!= (const Fraction& frac) const
    {
        return !(*this == frac);
    }
    // 输入输出
    friend ostream& operator<< (ostream& os, const Fraction& frac);
    friend istream& operator>> (istream& is, Fraction& dt);
    // 求最小公倍数
    static int MinCommMulti(int a, int b)
    {
        if(a < 0) a = -a;
        if(b < 0) b = -b;
        int n = max(a, b);
        int m = n;
        while(n%a || n%b)
            n += m;
        return n;
    }
    // 求最大公约数
    static int MaxCommFactor(int a, int b)
    {
        if(a < 0) a = -a;
        if(b < 0) b = -b;
        int n = min(a, b);
        while(n)
        {
            if(a%n == 0 && b%n == 0)
                break;
            n--;
        }
        return n;
    }
};
 
const double Fraction::threshold = 0.000001;
Fraction operator+(double a, const Fraction& b)
{
    return Fraction(a + (double)b);
}
Fraction operator-(double a, const Fraction& b)
{
    return -b + a;
}
Fraction operator*(double a, const Fraction& b)
{
    return Fraction(a*(double)b);
}
Fraction operator/(double a, const Fraction& b)
{
    return Fraction(a / (double)b);
}
ostream& operator<<(ostream& os, const Fraction& frac)
{
    if(!frac._denominator)
    {
        if(!frac._numerator)
            os << "NaN";
        else
            os << "Inf";
    }
    else
    {
        if(!frac._numerator)
            os << 0;
        else if(frac._denominator == 1.0)
            os << frac._numerator;
        else
            os << frac._numerator << '/' << frac._denominator;
    }
    return os;
}
istream& operator>> (istream& is, Fraction& frac)
{
    char o;
    is >> frac._numerator >> o >> frac._denominator;
    if(o != '/')
        frac = 0.0;
    else
        frac.simplify();
    return is;
}
// main
int main()
{
    Fraction frac1, frac2, frac3;
	while(1){
    cout << "Fraction1(a/b):" << endl;
    cin >> frac1;
    cout << frac1 << '\t' << (double)frac1 << endl;
    cout << "Fraction2(a/b):" << endl;
    cin >> frac2;
    cout << frac2 << '\t' << (double)frac2 << endl;
    cout << "operator(+ - * /)" << endl;
    char oper;
    cin >> oper;
    switch(oper)
    {
    case '+':
        cout << frac1 + frac2 << '\t' << (double)frac1 + (double)frac2 << endl;
        break;
    case '-':
        cout << frac1 - frac2 << '\t' << (double)frac1 - (double)frac2 << endl;
        break;
    case '*':
        cout << frac1 * frac2 << '\t' << (double)frac1 * (double)frac2 << endl;
        break;
    case '/':
        cout << frac1 / frac2 << '\t' << (double)frac1 / (double)frac2 << endl;
        break;
    }
	cout<<"go on:"<<endl;}
    return 0;
}