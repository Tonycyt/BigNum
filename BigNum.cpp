#include<string>
#include<deque>
#include<cstdio>
#include<iostream>
#include<stdexcept>
using namespace std;
inline string getstr(){
	string s;
	char ch;
	while((ch=getchar())!='\n'&&ch!=' ') s+=ch;
	return s;
}
inline string ulltostr(const unsigned long long&Num){
	unsigned long long _Num=Num;
	string s="";
	while(_Num!=0){
		s=char(_Num%10+48)+s;
		_Num/=10;
	}
	if(s=="") s="0";
	return s;
}
inline string slltostr(const signed long long&Num){
	if(Num>=0) return ulltostr(Num);
	else return "-"+ulltostr(-Num);
}
inline string uitostr(const unsigned&Num){
	unsigned _Num=Num;
	string s="";
	while(_Num!=0){
		s=char(_Num%10+48)+s;
		_Num/=10;
	}
	if(s=="") s="0";
	return s;
}
inline string sitostr(const signed&Num){
	if(Num>=0) return uitostr(Num);
	else return "-"+uitostr(-Num);
}
inline string ustostr(const unsigned short&Num){
	unsigned short _Num=Num;
	string s="";
	while(_Num!=0){
		s=char(_Num%10+48)+s;
		_Num/=10;
	}
	if(s=="") s="0";
	return s;
}
inline string sstostr(const signed short&Num){
	if(Num>=0) return ustostr(Num);
	else return "-"+ustostr(-Num);
}
struct BigNum{
	deque<signed> num;
	signed val;
	BigNum();
	BigNum(const BigNum&);
	BigNum(const signed long long&);
	BigNum(const unsigned long long&);
	BigNum(const signed&);
	BigNum(const unsigned&);
	BigNum(const signed short&);
	BigNum(const unsigned short&);
	BigNum(const deque<signed>&,const signed&);
	BigNum(const string&);
	BigNum(const string&,const signed&);
	void _cancel_zero();
	const BigNum operator+()const{return (*this);}
	const BigNum operator-()const{return BigNum(num,-val);}
	const BigNum operator+(const BigNum&)const;
	const BigNum operator-(const BigNum&)const;
	const BigNum operator*(const BigNum&)const;
	const BigNum operator/(const BigNum&)const;
	const BigNum operator%(const BigNum&)const;
	const BigNum operator+=(const BigNum&bignum){return (*this)=(*this)+bignum;}
	const BigNum operator-=(const BigNum&bignum){return (*this)=(*this)-bignum;}
	const BigNum operator*=(const BigNum&bignum){return (*this)=(*this)*bignum;}
	const BigNum operator/=(const BigNum&bignum){return (*this)=(*this)/bignum;}
	const BigNum operator%=(const BigNum&bignum){return (*this)=(*this)%bignum;}
	const BigNum operator++(){return (*this)+=BigNum("1");}
	const BigNum operator--(){return (*this)-=BigNum("1");}
	const BigNum operator++(signed _self_plus_val){BigNum _self_plus_help_bignum((*this));++(*this);return _self_plus_help_bignum;}
	const BigNum operator--(signed _self_minus_val){BigNum _self_minus_help_bignum((*this));--(*this);return _self_minus_help_bignum;}
	const bool operator<(const BigNum&)const;
	const bool operator>(const BigNum&)const;
	const bool operator==(const BigNum&bignum)const{return num==bignum.num&&val==bignum.val;}
	const bool operator!=(const BigNum&bignum)const{return num!=bignum.num||val!=bignum.val;}
	const bool operator>=(const BigNum&bignum)const{return (*this)==bignum||(*this)>bignum;}
	const bool operator<=(const BigNum&bignum)const{return (*this)==bignum||(*this)<bignum;}
};
BigNum zero_bignum("0");
pair<BigNum,BigNum> div(const BigNum&a,const BigNum&b);
istream&operator>>(istream&,BigNum&);
ostream&operator<<(ostream&,const BigNum&);
inline BigNum getBigNum();
inline void putBigNum(const BigNum&);
const BigNum pow(const BigNum&,const unsigned long long&);
const BigNum pow(const BigNum&,const unsigned long long&,const BigNum&);
BigNum::BigNum():val(1){}
BigNum::BigNum(const BigNum&bignum){(*this)=bignum;}
BigNum::BigNum(const signed long long&bignumnum){(*this)=BigNum(slltostr(bignumnum));}
BigNum::BigNum(const unsigned long long&bignumnum){(*this)=BigNum(ulltostr(bignumnum));}
BigNum::BigNum(const signed&bignumnum){(*this)=BigNum(sitostr(bignumnum));}
BigNum::BigNum(const unsigned&bignumnum){(*this)=BigNum(uitostr(bignumnum));}
BigNum::BigNum(const signed short&bignumnum){(*this)=BigNum(sstostr(bignumnum));}
BigNum::BigNum(const unsigned short&bignumnum){(*this)=BigNum(ustostr(bignumnum));}
BigNum::BigNum(const deque<signed>&bignumnum,const signed&bignumval=1):num(bignumnum),val(bignumval){}
BigNum::BigNum(const string&bignums,const signed&bignumval):val(bignumval){
	for(signed i=0;i<bignums.size();i++) num.push_front(bignums[i]-48);
}
BigNum::BigNum(const string&bignums){
	if(bignums[0]=='-'){
		val=-1;
		for(signed i=1;i<bignums.size();i++) num.push_front(bignums[i]-48);
	}
	else{
		val=1;
		for(signed i=0;i<bignums.size();i++) num.push_front(bignums[i]-48);
	}
}
void BigNum::_cancel_zero(){
	for(signed i=num.size()-1;i>-1&&num[i]==0;i--) num.pop_back();
	if(num.size()==0) (*this)=zero_bignum;
}
const BigNum BigNum::operator+(const BigNum&bignum)const{
	if(val==-1&&bignum.val==-1) return -((-(*this))+(-bignum));
	if(val==-1) return bignum-(-(*this));
	if(bignum.val==-1) return (*this)-(-bignum);
	if((*this)==zero_bignum) return bignum;
	if(bignum==zero_bignum) return(*this);
	BigNum sum;
	for(signed i=0;i<=num.size()||i<=bignum.num.size();i++){
		sum.num.push_back(0);
		if(i<num.size()) sum.num[i]+=num[i];
		if(i<bignum.num.size()) sum.num[i]+=bignum.num[i];
		if(i!=0)
			if(sum.num[i-1]>9) sum.num[i-1]-=10,sum.num[i]++;
	}
	sum._cancel_zero();
	if(sum.num.size()==0) return zero_bignum;
	return sum;
}
const BigNum BigNum::operator-(const BigNum&bignum)const{
	if(val==-1&&bignum.val==-1) return (-bignum)-(-(*this));
	if(val==-1) return -(bignum+(-(*this)));
	if(bignum.val==-1) return (*this)+(-bignum);
	if((*this)<bignum) return -(bignum-(*this));
	if((*this)==zero_bignum) return (-bignum);
	if(bignum==zero_bignum) return (*this);
	BigNum diff;
	for(signed i=0;i<num.size();i++){
		diff.num.push_back(num[i]);
		if(i<bignum.num.size()) diff.num[i]-=bignum.num[i];
		if(i!=0)
			if(diff.num[i-1]<0) diff.num[i-1]+=10,diff.num[i]--;
	}
	diff._cancel_zero();
	if(diff.num.size()==0) return zero_bignum;
	return diff;
}
const BigNum BigNum::operator*(const BigNum&bignum)const{
	if((*this)==zero_bignum||bignum==zero_bignum) return zero_bignum;
	if(val==-1&&bignum.val==-1) return BigNum(num,1)*BigNum(bignum.num,1);
	if(val==-1) return BigNum((BigNum(num,1)*bignum).num,-1);
	if(bignum.val==-1) return BigNum((BigNum(bignum.num,1)*(*this)).num,-1);
	if((*this)==zero_bignum||bignum==zero_bignum) return zero_bignum;
	BigNum prod;
	for(signed i=0;i<num.size()+bignum.num.size();i++) prod.num.push_back(0);
	for(signed i=0;i<num.size();i++)
		for(signed j=0;j<bignum.num.size();j++) prod.num[i+j]+=num[i]*bignum.num[j];
	for(signed i=0;i<prod.num.size();i++){
		prod.num[i+1]+=prod.num[i]/10;
		prod.num[i]%=10;
	}
	prod._cancel_zero();
	return prod;
}
pair<BigNum,BigNum> div(const BigNum&a,const BigNum&b){
	if(b==zero_bignum) throw invalid_argument("Denominator cannot be zero");
	if(a==zero_bignum) return {zero_bignum,zero_bignum};
	if(a<0&&b<0) return {div(-a,-b).first,-div(-a,-b).second};
	if(a<0) return {-div(-a,b).first,-div(-a,b).second};
	if(b<0) return {-div(a,-b).first,div(a,-b).second};
	if(a<b) return {zero_bignum,a};
	deque<signed> _x=a.num;
	signed _g=_x.front();
	_x.pop_front();
	BigNum __x(_x,1);
	BigNum _q,_r;
	if(_x.size()!=0){
		pair<BigNum,BigNum> _m=div(__x,b);
		_q=_m.first,_r=_m.second;
	}
	else _q=0,_r=0;
	_q*=BigNum("10"),_r*=BigNum("10");
	_r+=BigNum(_g);
	while(_r>=b) _r-=b,_q++;
	return {_q,_r};
}
const BigNum BigNum::operator/(const BigNum&bignum)const{return div((*this),bignum).first;}
const BigNum BigNum::operator%(const BigNum&bignum)const{return div((*this),bignum).second;} 
const bool BigNum::operator<(const BigNum&bignum)const{
	if(val==-1&&bignum.val==-1) return BigNum(num,1)>BigNum(bignum.num,1);
	if(val==-1) return 1;
	if(bignum.val==-1) return 0;
	if(num.size()==bignum.num.size())
		for(signed i=num.size()-1;i>-1;i--)	
			if(num[i]!=bignum.num[i]) return num[i]<bignum.num[i];
	return num.size()<bignum.num.size();
}
const bool BigNum::operator>(const BigNum&bignum)const{
	if(val==-1&&bignum.val==-1) return BigNum(num,1)<BigNum(bignum.num,1);
	if(val==-1) return 0;
	if(bignum.val==-1) return 1;
	if(num.size()==bignum.num.size())
		for(signed i=num.size()-1;i>-1;i--)
			if(num[i]!=bignum.num[i]) return num[i]>bignum.num[i];
	return num.size()>bignum.num.size();
}
istream&operator>>(istream&instream,BigNum&bignum){
	string bignumstr;
	instream>>bignumstr;
	bignum=BigNum(bignumstr);
	return instream;
}
ostream&operator<<(ostream&outstream,const BigNum&bignum){
	if(bignum.val==-1) outstream<<'-';
	for(signed i=bignum.num.size()-1;i>-1;i--) outstream<<bignum.num[i];
	return outstream;
}
inline BigNum getBigNum(){return BigNum(getstr());}
inline void putBigNum(const BigNum&bignum){
	if(bignum.val==-1) putchar('-');
	for(signed i=bignum.num.size()-1;i>-1;i--) putchar(bignum.num[i]+48);
}
const BigNum pow(const BigNum&_pow_base,const unsigned long long&_pow_index){
	if(_pow_base==zero_bignum) throw invalid_argument("Base cannot be zero");
	if(_pow_index==0) return BigNum("1");
	unsigned long long _new_pow_index=_pow_index>>1;
	BigNum _new_pow_anti=pow(_pow_base,_new_pow_index);
	if(_pow_index%2==0) return _new_pow_anti*_new_pow_anti;
	return _new_pow_anti*_new_pow_anti*_pow_base;
}
const BigNum pow(const BigNum&_pow_base,const unsigned long long&_pow_index,const BigNum&_pow_mod){
	if(_pow_base==zero_bignum) throw invalid_argument("Base cannot be zero");
	if(_pow_index==0) return BigNum("1");
	unsigned long long _new_pow_index=_pow_index/2;
	BigNum _new_pow_anti=pow(_pow_base,_new_pow_index)%_pow_mod;
	if(_pow_index%2==0) return _new_pow_anti*_new_pow_anti%_pow_mod;
	return _new_pow_anti*_new_pow_anti*_pow_base%_pow_mod;
}

