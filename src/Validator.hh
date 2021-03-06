// -*- mode: C++ -*-
// Time-stamp: "2012-09-07 18:50:07 sb"

/*
  file       Validator.hh
  copyright  (c) Sebastian Blatt 2012

 */


#ifndef VALIDATOR_HH__B4757EC6_AF20_46F8_A030_98B6BF560EDE
#define VALIDATOR_HH__B4757EC6_AF20_46F8_A030_98B6BF560EDE

#define HAVE_BOOST 0

#include <limits>
#include <iostream>
#include <string>
#include <typeinfo>

#if HAVE_BOOST
#include <boost/regex.hpp>
#endif // HAVE_BOOST

template <typename T>
class Validator {
  private:
    // Do not copy, but link on copy constructor to allow logical recursion.
    // This means the derived classes have to implement the copy constructor.
    Validator(const Validator&){}
  public:
    Validator(){}

    virtual bool Validate(const T& t) const = 0;
    bool operator()(const T& t) const {
      //std::cout << "Validating on " << *this << std::endl;
      return Validate(t);
    }
    virtual std::ostream& InvalidMessage(const T& t, std::ostream& out) const = 0;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Validator<T>& val){
  std::string n = typeid(val).name();
  out << n;
  return out;
}

template <typename T>
class ValidatorTrue : public Validator<T> {
  public:
    bool Validate(const T&) const {return true;}
    std::ostream& InvalidMessage(const T&, std::ostream& out) const {
      out << "Programmer error: ValidatorTrue<T> always validates.";
      return out;
    }
};

template <typename T>
class ValidatorNot : public Validator<T> {
  private:
    const Validator<T>& validator;
  public:
    // important: copy ctor needs to link, not copy!
    ValidatorNot(const ValidatorNot& validator_)
      : Validator<T>(),
        validator(dynamic_cast<const Validator<T>&>(validator_))
    {}
    ValidatorNot(const Validator<T>& validator_)
      : Validator<T>(),
        validator(validator_)
    {}
    bool Validate(const T& t) const {
      //std::cout << "ValidatorNot::Validate(" << t << ")" << std::endl;
      return !validator(t);
    }
    std::ostream& InvalidMessage(const T& t, std::ostream& out) const {
      out << "!( ";
      validator.InvalidMessage(t, out);
      out << " )";
      return out;
    }
};

template <typename T>
class ValidatorAnd : public Validator<T> {
  private:
    const Validator<T>& validator1;
    const Validator<T>& validator2;

    // hide this since it makes no sense
    ValidatorAnd(const ValidatorAnd& validator_) {}
  public:
    ValidatorAnd(const Validator<T>& validator1_,
                 const Validator<T>& validator2_)
      : validator1(validator1_),
        validator2(validator2_)
    {}
    bool Validate(const T& t) const {
      return validator1(t) && validator2(t);
    }
    std::ostream& InvalidMessage(const T& t, std::ostream& out) const {
      out << "(";
      validator1.InvalidMessage(t, out);
      out << " && ";
      validator2.InvalidMessage(t, out);
      out << ")";
      return out;
    }
};

template <typename T>
class ValidatorOr : public Validator<T> {
  private:
    const Validator<T>& validator1;
    const Validator<T>& validator2;

    // hide this since it makes no sense
    ValidatorOr(const ValidatorOr& validator_) {}
  public:
    ValidatorOr(const Validator<T>& validator1_,
                const Validator<T>& validator2_)
      : validator1(validator1_),
        validator2(validator2_)
    {}
    bool Validate(const T& t) const {
      return validator1(t) || validator2(t);
    }
    std::ostream& InvalidMessage(const T& t, std::ostream& out) const {
      out << "(";
      validator1.InvalidMessage(t, out);
      out << " || ";
      validator2.InvalidMessage(t, out);
      out << ")";
      return out;
    }
};


// Validate a <= x <= b. Type T needs to implement operator<=.
// Default to std::numeric_limits<T> for numeric types T.
template <typename T>
class ValidatorRange : public Validator<T> {
  private:
    T min_inclusive;
    T max_inclusive;

    // no copy
    ValidatorRange(const ValidatorRange&)
      : Validator<T>()
    {}
  public:
    ValidatorRange()
      : min_inclusive(std::numeric_limits<T>::min()),
        max_inclusive(std::numeric_limits<T>::max())
    {
      if(std::numeric_limits<T>::has_denorm == std::denorm_present){
        min_inclusive = -max_inclusive;
      }
    }
    ValidatorRange(const T& min_inclusive_, const T& max_inclusive_)
      : min_inclusive(min_inclusive_),
        max_inclusive(max_inclusive_)
    {}
    bool Validate(const T& t) const {
      //std::cout << "ValidatorRange::Validate(" << t << ")" << std::endl;
      return (min_inclusive <= t && t <= max_inclusive);
    }
    const T& GetMinInclusive() const {return min_inclusive;}
    const T& GetMaxInclusive() const {return max_inclusive;}

    std::ostream& InvalidMessage(const T& t, std::ostream& out) const {
      out << t << " out of range [" << min_inclusive << ", "
          << max_inclusive << "]";
      return out;
    }
};

#if HAVE_BOOST
class ValidatorRegex : public Validator<std::string> {
  private:
    boost::regex r;
    ValidatorRegex(const ValidatorRegex&)
      : Validator<std::string>()
    {}
  public:
    ValidatorRegex(const std::string& regex_string = ".*")
      : r(boost::regex(regex_string))
    {}
    bool Validate(const std::string& t) const {
      return boost::regex_match(t, r);
    }
    std::ostream& InvalidMessage(const std::string& t, std::ostream& out) const {
      out << t << " does not match " << r;
      return out;
    }
};
#endif // HAVE_BOOST

#endif // VALIDATOR_HH__B4757EC6_AF20_46F8_A030_98B6BF560EDE

// Validator.hh ends here
