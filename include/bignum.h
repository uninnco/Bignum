#pragma once

#include <iostream>
#include <vector>

/**
 * @file bignum.h
 * @brief 大数运算
 * @details 用于大数的加减乘除
 * @version 1.0
 * @author 荣立飞 朱晨
 * @date 2017-8-14
 */
using namespace std;
/**
 * @brief 大数类实现
 */
class Bignum
{
public:
    /**
     * @brief 构造函数
     * @prama str 输入的大数字符串
     */
    Bignum(string const& str =string());
    /**
     * @brief 重载=
     * @prama bn 大数对象
     */
    Bignum& operator=(Bignum const& bn);
    /**
     * @brief 进位类
     */
    class Carry
    {
    public:
        /**
         * @brief 构造函数
         * @prama carr 输入的进位数值
         */
        Carry(int& carr);
        /**
         * @brief 仿函数 进位操作
         * @prama n 该位上的数值
         * @return 进位值
         */
        inline int operator()(int n);

    private:
        int& carr_;///进位的数值
    };
    /**
     * @brief 重载+
     * @right '+'右边的大数对象
     * @return 相加的结果
     */
    Bignum operator+(Bignum const& right)const;
    /**
     * @brief 重载-
     * @right '-'右边的大数对象
     * @return 相加的结果
     */
    Bignum operator-(Bignum const& right)const;
    /**
     * @brief 重载+
     * @right '*'右边的大数对象
     * @return 相加的结果
     */
    Bignum operator*(Bignum const& right)const;
    /**
     * @brief 重载+
     * @right '/'右边的大数对象
     * @return 相加的结果
     */
    Bignum operator/(Bignum const& right)const;
    /**
     * @brief 重载<<
     * @prama os 输出流对象
     * @prama bn 大数对象
     * @return 输出流对象
     */
    friend ostream& operator<<(ostream& os,Bignum const& bn);
    int compare(Bignum const& rbn);
    /**
     * @brief 重载后缀++
     * @return 加1的结果
     */
    Bignum operator++(int);
private:
    /**
     * @brief 获取大数对象存放数值容器的大小
     */
    size_t Length()const;
    /**
     * @brief 重新设置大数对象存放数值容器的大小
     */
    void Resize(size_t size);
    vector<int> nums_;
    bool negative_flag_;
};
#include "carry.inl"
