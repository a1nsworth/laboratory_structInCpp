#include <iostream>
#include <numeric>
#include <exception>
#include <vector>
#include <functional>

namespace lbw {

    /* Дробь с числителем и знаменателем.*/
    template<typename T>
    class Fraction {
    private:
        T _numenator;
        T _denominator;

    public:
        /**
         * Конструктор по умолча
         * Конструктор по умолчанию, инициализирует числитель 0, а знаменатель 1.
         */
        Fraction() {
            _numenator = 0;
            _denominator = 1;
        }

        /**
         * Инициализирует дробь с числителем и знаменателем, сокращает их, если
         * это возможно. В случае, если только числитель или знаменатель
         * отрицательный, знак минус переходит к числителю.
         *
         * @param numenator Числитель дроби.
         * @param denominator Знаменатель дроби.
         *
         * @throw Выбрасывает исключение, если Знаменатель равен 0.
         */
        Fraction(T numenator, T denominator) {
            try {
                if (denominator == 0)
                    throw static_cast<std::string>("Divide by zero error in fraction!");

                _numenator = std::abs(numenator);
                _denominator = std::abs(denominator);

                auto gcm = std::gcd(_numenator, _denominator);
                _numenator /= gcm;
                _denominator /= gcm;
                if (numenator * denominator < 0)
                    _numenator *= -1;
            }
            catch (const std::string &str) {
                std::cerr << "Error: " << str << '\n';
            }
        }

        /*
         * Сокращает дробь.
         */
        void reduceFraction() {
            auto _gcd = std::gcd(_numenator, _denominator);
            _numenator /= _gcd;
            _denominator /= _gcd;
        }

        friend std::ostream &operator<<(std::ostream &out, const Fraction &f) {
            if (f._denominator == 1)
                out << f._numenator;
            else
                out << f._numenator << "/" << f._denominator;
            return out;
        }

        friend std::istream &operator>>(std::istream &in, Fraction &f) {
            T numenator;
            T denominator;
            in >> numenator;
            try {
                in >> denominator;
                if (denominator == 0)
                    throw static_cast<std::string>("Divide by zero error in fraction!");

                f = Fraction(numenator, denominator);
            }
            catch (const std::string &str) {
                std::cerr << "Error: " << str << '\n';
            }

            return in;
        }

        Fraction operator+(const Fraction &other) const {
            auto _lcm = std::lcm(_denominator, other._denominator);

            Fraction res;
            res._numenator = _numenator + (_lcm / _denominator) + other._numenator * (_lcm / other._denominator);

            return res.reduceFraction();
        }

        Fraction operator-(const Fraction &other) const {
            return (Fraction) {_numenator, _denominator} + (Fraction) {-other._numenator, other._denominator};
        }

        Fraction operator*(const Fraction &other) const {
            auto _gcd = std::gcd(_numenator, other._denominator);
            auto _gcd2 = std::gcd(other._numerator, _denominator);

            return {(_numenator / _gcd) * (other._numenator / _gcd2),
                    (_denominator / _gcd2) * (other._denominator / _gcd)};
        }

        Fraction operator/(const Fraction &other) {
            return (Fraction) {_numenator, _denominator} * (Fraction) {other._denominator, other._numenator};
        }
    };

    /* Материальная точка, с позицией, с скоростью и ускорением*/
    class MaterialPoint {
    private:
        double _position;
        double _speed;
        double _asseleration;

    public:
        /**
         * Инициализирует материальную точку.
         *
         * @param position Положение материальной точки в системе координат x.
         * @param speed Скорость точки
         * @param asseleration Ускорение точки
         */
        MaterialPoint(double position = 0, double speed = 0, double asseleration = 0) {
            _position = position;
            _speed = speed;
            _asseleration = asseleration;
        }

        /**
         * Устанавливает скорость
         *
         * @param speed Скорость
         */
        void setSpeed(const double speed) {
            _speed = speed;
        }

        /**
         * Устанавливает ускорение.
         *
         * @param speed Ускорение
         */
        void setAsseleration(const double asseleration) {
            _asseleration = asseleration;
        }

        /**
         * Устанавливает позицию.
         *
         * @param position Позиция
         */
        void setPosition(const double position) {
            _position = position;
        }

        /**
         * @return Возвращает позицию
         */
        double getPosition() const {
            return _position;
        }

        /**
         * @return Возвращает скорость
         */
        double getSpeed() const {
            return _speed;
        }

        /**
         * @return Возвращает ускорение
         */
        double getAsseleration() const {
            return _asseleration;
        }
    };

    /**
     * Множество на основе битов
     * */
    class BitSet {
    private:
        // максимальное поддерживаемое значение битсетом как таковым
        static const unsigned _MAX_VALUE_SUPPORTED = 31;

        // максимальное поддерживаемое значение
        // для создаваемой структуры
        const unsigned _maxValue = _MAX_VALUE_SUPPORTED;

        // поле для хранения значений
        uint32_t _data = 0;

        // мощность множества
        unsigned _power = 0;

        /**
         * Инициализирует множество исходя из переданого значения другого множества.
         *
         * @param data значение другого множества
         * @param maxValue максимальны элемент переданого значения
         */
        BitSet(const uint32_t data, const unsigned maxValue) : BitSet(maxValue) {
            _data = data;
            for (unsigned i = 0; i <= maxValue; ++i)
                if (find(i))
                    _power++;
        }

    public:
        BitSet() = default;

        /**
         * Инициализирует множество из вектора
         *
         * @param v вектор для инициализации множества
         */
        BitSet(const std::vector<unsigned> &v) : BitSet(*std::max_element(v.begin(), v.end())) {
            for (auto &element: v)
                insert(element);
        }

        /**
         * Инициализирует множество из другого множества
         *
         * @param a множество для инициализации множества
         */
        BitSet(const BitSet &a) : BitSet(a._maxValue) {
            _data = a._data;
            _power = a._power;
        }

        /**
         * Инициализирует пустое множество с переданным максимальным значением
         *
         * @param maxValue максимальное значение хранящееся в множестве
         */
        BitSet(const unsigned maxValue) : _maxValue(maxValue) {
            try {
                if (maxValue > _MAX_VALUE_SUPPORTED)
                    throw std::invalid_argument("Value is greater than allowed");
            } catch (const std::exception &e) {
                std::cerr << e.what();
            }
        }

        /**
         * Проверяет на отсутствие элементов в множестве
         *
         * @return возвращает true, если множество пустое иначе false
         */
        bool empty() const {
            return _power;
        }

        /**
         * Добовляет элемент в множество.
         *
         * @param x элемент для добавления
         * @throws Выбрасывает исключение, если x больше максимально допустимого элемента множества
         */
        void insert(const unsigned x) {
            try {
                if (x > _maxValue)
                    throw std::invalid_argument("Value is greater than max allowed element");
                _power = !find(x) ? _power + 1 : _power;
                _data |= (1 << x);
            } catch (const std::exception &e) {
                std::cerr << e.what();
            }
        }

        /**
         * Проверяет на нахождение элемента в множестве.
         *
         * @param x элемент для поиска
         * @return Возвращает true, если элемент есть в множестве иначе false.
         */
        bool find(const unsigned x) const {
            return (_data >> x) & 1;
        }

        /**
         * Поиск первого элемента удовлетворяещего функции-предикату от [begin; end).
         *
         * @param begin начало поиска
         * @param end конец поиска не включительно
         * @param binaryPredicate унарный предикат.
         * @throw Выбрасывает исключение если begin > end или end больше допустимого максимального в множестве
         * @return Возвращает первый элемент удовлетворяющий функции-предикату, если элемент не найден возвращает
         * Максимально допустимый элемент любого множества + 1;
         */
        unsigned find(unsigned begin, const unsigned end, std::function<bool(unsigned)> binaryPredicate) const {
            try {
                if (begin > end)
                    throw std::invalid_argument("Begin greater than end");
                else if (end > _maxValue)
                    throw std::invalid_argument("Value is greater than max allowed element");

                while (begin != end) {
                    if (find(begin) && binaryPredicate(begin))
                        return begin;
                    begin++;
                }

            } catch (const std::exception &e) {
                std::cerr << e.what();
            }

            return _MAX_VALUE_SUPPORTED + 1;
        }

        /**
         * Удаляет элемент из множества.
         *
         * @param x элемент для удаления
         * @throws Выбрасывает исключение, если элемент больше максимального допустимого в множестве
         */
        void erase(const unsigned x) {
            try {
                if (x > _maxValue)
                    throw std::invalid_argument("Value is greater than max allowed element");

                _power = find(x) ? _power - 1 : _power;
                _data &= ~(1 << x);
            } catch (const std::exception &e) {
                std::cerr << e.what();
            }
        }

        /**
         * Удаляет элементы в множестве от [begin;end).
         *
         * @param begin начальная позиция
         * @param end конечна позиция не включительно
         * @throw Выбрасывает исключение, если begin >= end или end больше максимально допустимого значения в множестве
         */
        void erase(unsigned begin, const unsigned end) {
            try {
                if (begin >= end)
                    throw std::invalid_argument("Begin greater than end");
                else if (end > _maxValue)
                    throw std::invalid_argument("Value is greater than max allowed element");

                while (begin++ != end)
                    erase(begin);

            } catch (const std::exception &e) {
                std::cerr << e.what();
            }
        }

        /**
         * Удаляет элементы из множества от [begin;end) удовлетворяющие унарному бинарному придикату.
         *
         * @param begin начальная позиция
         * @param end конечная позиция не включительно
         * @param binaryPredicate бинарный предикат
         * @throw Выбрасывает исключение, если begin >= end или end больше максимально допустимого значения в множестве
         */
        void erase(unsigned begin, const unsigned end, std::function<bool(unsigned)> binaryPredicate) {
            try {
                if (begin > end)
                    throw std::invalid_argument("Begin greater than end");
                else if (end > _maxValue)
                    throw std::invalid_argument("Value is greater than max allowed element");
a1nsworth
                while (begin != end) {
                    if (find(begin) && binaryPredicate(begin))
                        erase(begin);
                    begin++;
                }
            } catch (const std::exception &e) {
                std::cerr << e.what();
            }
        }

        /**
         * @return Возвращает можность множества
         */
        unsigned getPower() const {
            return _power;
        }

        /**
         * Проверяет, является ли данное множество подмножеством множества set.
         * @param set множество
         * @return Возвращает true, если set является надмножеством данного множества, иначе false
         */
        bool isSubset(const BitSet &set) const {
            return (_data | set._data) == set._data;
        }

        /**
         * Проверяет, является ли subset множество подмножеством множества set.
         * @param subset множество
         * @param set множество
         * @return Возвращает true, если set является надмножеством subset множества, иначе false
         */
        static bool isSubset(const BitSet &subset, const BitSet &set) {
            return (set._data | subset._data) == set._data;
        }

        /**
         * Пересечение двух множеств lhs и rhs.
         *
         * @param lhs множество
         * @param rhs множество
         * @return Возращает множество которое является результатом пересечения двух множеств.
         */
        static BitSet insertions(const BitSet &lhs, const BitSet &rhs) {
            unsigned maxValue = 0;
            for (int i = _MAX_VALUE_SUPPORTED; i >= 0; i--)
                if (lhs.find(i) || rhs.find(i)) {
                    maxValue = i;
                    break;
                }

            return BitSet(lhs._data & rhs._data, maxValue);
        }

        /**
         * Объеденение двух множеств lhs и rhs.
         *
         * @param lhs множество
         * @param rhs множество
         * @return Возращает множество которое является результатом объеденения двух множеств.
         */
        static BitSet union_(const BitSet &lhs, const BitSet &rhs) {
            unsigned maxValue = 0;
            for (int i = _MAX_VALUE_SUPPORTED; i >= 0; i--)
                if (lhs.find(i) || rhs.find(i)) {
                    maxValue = i;
                    break;
                }

            return BitSet(lhs._data | rhs._data, maxValue);
        }


        /**
         * Дополнение множества set.
         *
         * @param set множество
         * @return Возращает множество которое является результатом дополнения множества.
         */
        static BitSet addition(const BitSet &set) {
            unsigned maxValue = 0;
            for (int i = _MAX_VALUE_SUPPORTED; i >= 0; i--)
                if (!set.find(i)) {
                    maxValue = i;
                    break;
                }

            return BitSet(~set._data, maxValue);
        }

        /**
         * Разница двух множеств lhs и rhs.
         *
         * @param lhs множество
         * @param rhs множество
         * @return Возращает множество которое является результатом разницы двух множеств.
         */
        static BitSet difference(const BitSet &lhs, const BitSet &rhs) {
            unsigned maxValue = 0;
            for (int i = _MAX_VALUE_SUPPORTED; i >= 0; i--)
                if (lhs.find(i) || rhs.find(i)) {
                    maxValue = i;
                    break;
                }

            return BitSet(lhs._data & addition(rhs)._data, maxValue);
        }

        /**
         * Симметрическа разность двух множеств lhs и rhs.
         *
         * @param lhs множество
         * @param rhs множество
         * @return Возращает множество которое является результатом симметрической разницы двух множеств.
         */
        static BitSet symmetricDifference(const BitSet &lhs, const BitSet &rhs) {
            unsigned maxValue = 0;
            for (int i = _MAX_VALUE_SUPPORTED; i >= 0; i--)
                if (lhs.find(i) && !rhs.find(i) || !lhs.find(i) && rhs.find(i)) {
                    maxValue = i;
                    break;
                }

            return BitSet(lhs._data ^ addition(rhs)._data, maxValue);
        }

        BitSet operator=(const BitSet &other) {
            return BitSet(other);
        }

        friend std::ostream &operator<<(std::ostream &out, const BitSet &a) {
            out << '{';
            for (unsigned i = 0; i <= _MAX_VALUE_SUPPORTED; ++i)
                if (a.find(i))
                    out << i << ',';
            out << "\b}";

            return out;
        }

        friend std::istream &operator>>(std::istream &in, BitSet &a) {
            unsigned size, maxValue;
            in >> size >> maxValue;

            BitSet t(maxValue);
            for (size_t i = 0; i < size; ++i) {
                unsigned x;
                in >> x;

                t.insert(x);
            }
            a = t;

            return in;
        }

        bool operator==(const BitSet &other) const {
            return _data == other._data;
        }

        bool operator!=(const BitSet &other) const {
            return _data != other._data;
        }
    };
} // namespace lbw

int main() {


    return 0;
}