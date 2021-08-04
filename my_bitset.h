#include <iostream>
using namespace std;

template <int m_size>
class my_bitset
{
  public:
          my_bitset<m_size>();
          my_bitset<m_size>(int y);
          my_bitset<m_size>(const my_bitset<m_size> &str);
          ~my_bitset<m_size>();
          my_bitset<m_size>& set();
          my_bitset<m_size>& reset();
          my_bitset<m_size>& set(int pos,bool val = true);
          bool operator[] (int position) const;
          my_bitset<m_size>& operator=(bool b);
          my_bitset<m_size>& operator=(const my_bitset<m_size>& str); 

          friend my_bitset<m_size> operator&(const my_bitset<m_size>& left, const my_bitset<m_size>& right)
          {
            my_bitset<m_size> tmp(left);

              for(int i = 0 ; i < tmp.y ; ++i)
              {
                tmp.arr[i] &= right.arr[i];
              }
    
            return tmp;
          }

          friend my_bitset<m_size> operator|(const my_bitset<m_size>& left, const my_bitset<m_size>& right)
          {
            my_bitset<m_size> tmp(left);

              for(int i = 0 ; i < tmp.y ; ++i)
              {
                tmp.arr[i] |= right.arr[i];
              }
    
            return tmp;
          }

          friend my_bitset<m_size> operator^(const my_bitset<m_size>& left, const my_bitset<m_size>& right)
          {
            my_bitset<m_size> tmp(left);

              for(int i = 0 ; i < tmp.y ; ++i)
              {
                tmp.arr[i] ^= right.arr[i];
              }
    
            return tmp;
          }

          friend ostream& operator<<(ostream &ostr, my_bitset<m_size> str)
          {  
             if(m_size > 32)
             {
               int tmp = (m_size % 32)-1;
               int temp = m_size/32;

              for(int j = temp; j > 0;--j)
              {
                for(int i = tmp  ; i >= 0; --i)
                {
                  if(str.arr[j] & (1 << i))
                {
                  ostr << true;
                } 

                else
                {
                  ostr << false;
                }
                }
                tmp = 31;
              }   
              
              for(int i = 31  ;i >= 0;--i)
              {
                if(str.arr[0] & (1 << i))
                {
                  ostr << true;
                } 

                else
                {
                  ostr << false;
                }
              }
             }
             else
             {
               for(int i = m_size - 1  ;i >= 0;--i)
              {
                if(str.arr[0] & (1 << i))
                {
                  ostr << true;
                } 

                else
                {
                  ostr << false;
                }
              }
             }
             return (ostr);
          }
          
  private:
          
          int y = 1;
          int* arr;
          
};



template<int m_size>
my_bitset<m_size>::my_bitset()
{
  int k = m_size;
    while(k/33)
    {
      y += 1;  
      k = k - 32;
    }

   arr = new int[y];    
   for(int i = 0;i < y;++i) {arr[i]=0;}
   
}

template<int m_size>
my_bitset<m_size>::my_bitset(int tmp)
{

    int k = m_size;
    while(k/33)
    {
      y += 1;  
      k = k - 32;
    }

   arr = new int[y];    
   for(int i = 1;i < y;++i) {arr[i]=0;}
   arr[0] = tmp;

}

template<int m_size>
my_bitset<m_size>::my_bitset(const my_bitset<m_size> &str)
{
  this->y = str.y;
  this->arr = new int[str.y];
  for(int i = 0; i < str.y; ++i)
  {
    this->arr[i] = str.arr[i];
  }
  
}

template<int m_size>
my_bitset<m_size>::~my_bitset<m_size>()
{
  delete arr; 
}

template<int m_size>
my_bitset<m_size>& my_bitset<m_size>::set()
{

  int tmp = m_size / 32;
  for(int i = 0; i <= tmp; ++i)
  {
    this->arr[i] = -1;
  }

  return *this;
}

template<int m_size>
my_bitset<m_size>& my_bitset<m_size>::set(int pos,bool val )
{
  if(pos >= 32)
  {
    int temp = pos/32;
    int tmp = pos % 32;
  
    if( val )
    {
      this->arr[temp] |= (1 << tmp); 
      return *this; 
    }

    else
    {
      if(this->arr[temp] & (1 << tmp ))
      {
        this->arr[temp] ^= (1 << tmp );
      }
    
      return *this;
    }
  }
  else
  {
    
     if( val )
    {
      this->arr[0] |= (1 << pos); 
      return *this; 
    }

    else
    {
      if(this->arr[0] & (1 << pos ))
      {
        this->arr[0] ^= (1 << pos );
      }
    
      return *this;
    }
  }
}

template<int m_size>
my_bitset<m_size>& my_bitset<m_size>::reset()
{
  
    int tmp = m_size / 32;
    for(int i = 0;i <= tmp; ++i)
    {
      this->arr[i] = 0;
    }
  
  return *this;
}

template<int m_size>
bool my_bitset<m_size>::operator[](int position) const
{
  if(m_size >= 32)
  {
    int tmp = position / 32;
    int temp = position % 32;
    if(this->arr[tmp] & (1 << temp))
    {
      return true;
    }
    return false;
  }
  else
  {
    if(this->arr[0] & (1 << position))
    {
      return true;
    }
    return false;
  }
}

template <int m_size>
my_bitset<m_size>& my_bitset<m_size>::operator=(bool bul)
{
  int tmp = m_size / 32;
  if(bul)
  {
    for(int i = 0; i <= tmp ; ++i )
    {
    this->arr[i] = -1;
    }
    return *this;
  }
  
  else
  {
    for(int i = 0; i <= tmp ; ++i )
    {
    this->arr[i] = 0;
    }
    return *this;
  }
}

template <int m_size>
my_bitset<m_size>& my_bitset<m_size>::operator=(const my_bitset<m_size>& str)
{
  int tmp = m_size / 32;
  this->y = str.y;
  
  for(int i = 1; i <= tmp ; ++i)
  {
    this->arr[i] = str.arr[i];
  }

  this->arr[0] = str.arr[0];


  return *this;
}