#include "../include/bignum.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>

using namespace std;

Bignum::Bignum(string const& str)
{
    if(str[0] =='-') negative_flag_ = true;
    else negative_flag_ = false;
    for(auto c:str ) {
        if(c == '-') {
            continue;
        }
        nums_.push_back(c-'0');
    }
}
Bignum& Bignum::operator=(Bignum const& bn)
{
    this->nums_ = bn.nums_;
    this->negative_flag_ = bn.negative_flag_;
    return *this;
}
Bignum::Carry::Carry(int& carr):carr_(carr) {}
Bignum Bignum::operator+(Bignum const& right)const
{
    Bignum res;
    Bignum lbn(*this);
    Bignum rbn(right);
    size_t maxlen = max(this->Length(),right.Length());
    lbn.Resize(maxlen);
    rbn.Resize(maxlen);
    if(lbn.negative_flag_ == rbn.negative_flag_ ) {
        transform(lbn.nums_.rbegin(),lbn.nums_.rend(),rbn.nums_.rbegin(),inserter(res.nums_,res.nums_.begin()),plus<int>());
        int carr(0);
        transform(res.nums_.begin(),res.nums_.end(),res.nums_.begin(),[&carr](int n) {
            n+=carr;
            carr = n/10;
            return n%10;
        });
        if(carr > 0) {
            res.nums_.push_back(carr);
        }
        reverse(res.nums_.begin(),res.nums_.end());
        res.negative_flag_ = lbn.negative_flag_;  //这里由于是同号相加，因此结果与两个数据的负号标志对齐
        return res;
    }
    if(lbn.negative_flag_ == true) {
        lbn.negative_flag_ = 0;
    }
    if(rbn.negative_flag_ == true) {
        rbn.negative_flag_ = 0;
    }
    return lbn-rbn;
}
Bignum Bignum::operator-(Bignum const& right)const
{
    Bignum res;
    Bignum lbn(*this);
    Bignum rbn(right);
    size_t maxlen = max(this->Length(),right.Length())+1;
    if(lbn.negative_flag_ == rbn.negative_flag_) {
        if(lbn.compare(rbn) == 0) {
            res.nums_.push_back(0);
            res.negative_flag_ = 0;
            return res;
        }
        if(lbn.compare(rbn) == 1) { //左边大于右边
            lbn.Resize(maxlen);
            rbn.Resize(maxlen);
            transform(lbn.nums_.rbegin(),lbn.nums_.rend(),rbn.nums_.rbegin(),inserter(res.nums_,res.nums_.begin()),minus<int>());    //左边减右边
            for(size_t i=0; i<res.nums_.size(); i++) {
                if(res.nums_[i] < 0) {
                    res.nums_[i+1] -= 1;
                    res.nums_[i] += 10;
                }
            }
            while(res.nums_.back() == 0) {
                res.nums_.pop_back();
            }
            reverse(res.nums_.begin(),res.nums_.end());
            res.negative_flag_ = lbn.negative_flag_;  //左边大于右边,因此结果负号标志与左边对齐
            return res;
        }
        if(lbn.compare(rbn) == -1) { //左边小于右边
            lbn.Resize(maxlen);
            rbn.Resize(maxlen);
            transform(rbn.nums_.rbegin(),rbn.nums_.rend(),lbn.nums_.rbegin(),inserter(res.nums_,res.nums_.begin()),minus<int>());   //右边减左边
            for(size_t i=0; i<res.nums_.size(); i++) {
                if(res.nums_[i] < 0) {
                    res.nums_[i+1] -= 1;
                    res.nums_[i] += 10;
                }
            }
            while(res.nums_.back() == 0) {
                res.nums_.pop_back();
            }
            reverse(res.nums_.begin(),res.nums_.end());
            res.negative_flag_ = !(lbn.negative_flag_);//结果的符号标志必然与左边的符号标志相反，
            //例如 a < b, 若a>0, a-b <0
            return res;
        }
    }
    if(lbn.negative_flag_ == true) {
        rbn.negative_flag_ = true;  //如果左边为负数，此时右边必然为正数，然后将-a-b转换成(-a)+(-b)
        return lbn + rbn;
    }
    if(rbn.negative_flag_ == true) {
        rbn.negative_flag_ = false;   //如果右边为负数，此时左边必然是正数，然后将a-(-b)转换成a+b
        return lbn + rbn;
    }
    return lbn;
}

Bignum Bignum::operator*(Bignum const& right)const
{
    Bignum res;
    Bignum temp;
    Bignum lbn(*this);
    Bignum rbn(right);
    if((lbn.Length() == 1&&lbn.nums_[0] == 0) ||(rbn.Length() == 1&&rbn.nums_[0] == 0)) {
        res.nums_.push_back(0);
        res.negative_flag_ = false;
        return res;
    }
    bool res_negative_flag;
    if(lbn.negative_flag_ == rbn.negative_flag_) {
        res_negative_flag = false;
    } else {
        res_negative_flag = true;
    }
    size_t size = rbn.Length();
    size_t maxlen = this->Length()+right.Length()+1;
    lbn.Resize(maxlen);
    rbn.Resize(maxlen);
    temp.Resize(maxlen);
    res.Resize(maxlen);
    auto rbn_it = rbn.nums_.rbegin();
    for(size_t i = 0; i <size; i++) {
        auto lbn_it = lbn.nums_.rbegin();
        auto temp_it = temp.nums_.rbegin();

        //  将lbn内的所有数字和rbn的从末尾的一位的10的i次方相乘
        //  乘积放在temp内
        //  然后res类加

        while(lbn_it != lbn.nums_.rend()) {
            *temp_it = (*lbn_it)*(*rbn_it);
            lbn_it++;
            temp_it++;
        }
        int carr(0);
        transform(temp.nums_.rbegin(),temp.nums_.rend(),temp.nums_.rbegin(),[&carr](int n) {
            //这里必须是反向
            n+=carr;
            carr = n/10;
            return n%10;
        });
        if(carr > 0) {
            temp.nums_.push_back(carr);
        }
        for(size_t j = 0; j < i; j++) {
            temp.nums_.push_back(0);   //temp移位
        }
        res = res+temp;
        int carr2(0);
        transform(res.nums_.rbegin(),res.nums_.rend(),res.nums_.rbegin(),[&carr2](int n) {
            //这里必须是反向
            n+=carr2;
            carr2 = n/10;
            return n%10;
        });
        if(carr2 > 0) {
            res.nums_.push_back(carr2);
        }
        auto res_it =res.nums_.begin();
        while(res_it != res.nums_.end()) { //去头部的0
            if(*res_it == 0)
                res.nums_.erase(res_it);
            else
                break;
        }
        if(i == size -1) {
            res.negative_flag_ = res_negative_flag;
            return res;
        }
        rbn_it++;
    }
    return res;
}
/*
 * 两种实现代码，一种方法
Bignum Bignum::operator*(Bignum const& right)const
{
    Bignum lbn(*this);
    Bignum rbn(right);
    Bignum res;
    Bignum unit("0");
    reverse(lbn.nums_.begin(),lbn.nums_.end());
    reverse(rbn.nums_.begin(),rbn.nums_.end());
    if(lbn.negative_flag_ == rbn.negative_flag_)  res.negative_flag_ = false;
    else res.negative_flag_ = true;
    if(lbn.compare(unit) == 0||rbn.compare(unit) == 0)	return unit;
    size_t maxlen = lbn.Length()+rbn.Length();
    res.Resize(maxlen);
    for(size_t i = 0; i< lbn.Length(); i++) {
        for(size_t j = 0; j< rbn.Length(); j++)
            res.nums_[i+j] += lbn.nums_[i]*rbn.nums_[j];
    }
    for(size_t i=0; i<res.Length(); i++) {
        int carry = res.nums_[i]/10;
        if(carry > 0) {
            if(i+1 == res.Length()) {
                res.nums_.push_back(carry);
            } else {
                res.nums_[i+1] += carry;
            }
            res.nums_[i] %= 10;
        }
    }

    reverse(res.nums_.begin(),res.nums_.end());
    return res;
}*/
Bignum Bignum::operator/(Bignum const& right)const
{
    Bignum res;
    Bignum lbn(*this);
    Bignum rbn(right);
    if(rbn.compare(Bignum("0")) == 0) {
        throw runtime_error("除数为0，运行错误");
    }
    bool res_negative_flag;
    if(lbn.negative_flag_ == rbn.negative_flag_)  res_negative_flag = false;
    else  res_negative_flag = true;
    lbn.negative_flag_ =false;
    size_t distance = lbn.Length() - rbn.Length();
    res.Resize(distance);
    for(; lbn.compare(rbn) !=-1 ;) {
        Bignum temp = rbn;
        temp.negative_flag_ =false;
        for(size_t i = 0; i < distance; i++)
            temp.nums_.push_back(0);
        size_t j = 0;
        while((lbn.compare(temp) == 1&&lbn.negative_flag_ == false)or(lbn.compare(temp) == 0)) {
            lbn = lbn - temp;
            j++;
        }
        size_t quot = j*pow(10,distance);
        ostringstream oss;
        oss << quot;
        res = res+Bignum(oss.str());
        distance--;
        if(lbn.compare(Bignum("0")) == 0) {
            res.negative_flag_ = res_negative_flag;
            reverse(res.nums_.begin(),res.nums_.end());
            while(res.nums_.back() == 0)
                res.nums_.pop_back();
            reverse(res.nums_.begin(),res.nums_.end());
            return res;
        }
    }
    res.negative_flag_ = res_negative_flag;
    reverse(res.nums_.begin(),res.nums_.end());
    while(res.nums_.back() == 0)
        res.nums_.pop_back();
    reverse(res.nums_.begin(),res.nums_.end());
    return res;


}
size_t Bignum::Length()const
{
    return nums_.size();
}
void Bignum::Resize(size_t size)
{
    size_t olen = nums_.size();
    nums_.resize(size);
    rotate(nums_.begin(),nums_.begin()+olen,nums_.end());
}
ostream& operator<<(ostream& os,Bignum const& bn)
{
    if(bn.negative_flag_== true) {
        os << "-";
    }
    if(bn.Length() == 1&& bn.nums_[0] == 0) {
        os <<0;
    } else {
        copy(bn.nums_.begin(),bn.nums_.end(),ostream_iterator<int>(os,""));
    }
    return os;
}
int Bignum::compare(Bignum const& rbn)
{
//compare只进行值比较,不做正负判断
    if(this->nums_.size() > rbn.nums_.size()) {
        return 1;//左边大于右边
    }
    if(this->nums_.size() < rbn.nums_.size()) {
        return -1;//左边小于右边
    }
    if(this->nums_.size() == rbn.nums_.size()) {
        auto lbn_it = this->nums_.begin();
        auto rbn_it = rbn.nums_.begin();
        while(lbn_it != this->nums_.end()) {
            if(*lbn_it == *rbn_it) {
                lbn_it++;
                rbn_it++;
                continue;
            }
            if(*lbn_it > *rbn_it) {
                return 1;//左边大于右边
            }
            if(*lbn_it < *rbn_it) {
                return -1;//左边小于右边
            }
        }
        return 0; //左边等于右边
    }
    return 0;
}
Bignum Bignum::operator++(int)
{
    Bignum temp(*this);
    Bignum unit;
    unit.nums_.push_back(1);
    *this = *this+unit;
    return temp;
}

