/*
* TODO: 
* 1. Implement iterators such as begin(), end() to allow integration with standard algorithms and range loops
* 2. Implement scalar arithmetic... ex.
    vec += 5;
    vec *= 2;
    vec /= 3;
* 3. Implement comparison operators such as == and !=
*/

export module vektor:vector;
import :types;
import std;

export namespace vektor {

    // * Restricts vektor_numeric to integer/floating type values while omitting boolean types
    template <typename T>
    concept vektor_numeric = (std::integral<T> || std::floating_point<T>) && !std::same_as<T, bool>;

    inline namespace naive {

        /**
        * @brief Fixed size mathematical vector
        * Stores D elements of type T in continious memory, all elements are value initialized
        * @tparam T Numeric element type
        * @tparam D Number of dimensions, must be greater than zero or will fail to compile
        **/
        template <vektor_numeric T, std::size_t D>
        class Vector {
            // * Catch invalid number of dimensions provided during compilation time
            static_assert(D > 0, "Dimensions must be greater than 0");

            private:
                std::array<T, D> m_data{};

            public:

            /**
            * @brief Access element without bounds checking
            * @param index Element index
            * @return Reference to requested element
            **/
            [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
                return m_data[index];
            }

            /**
            * @brief Access element without bounds checking
            * @param index Element index
            * @return Reference to requested element
            **/
            [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
                return m_data[index];
            }

            /**
            * @brief Access element with bounds checking
            * @param index Element index
            * @return Reference to requested element
            * @throws std::out_of_range if index is outside the vector's dimensions
            **/
            [[nodiscard]] constexpr T& at(std::size_t index) {
                return m_data.at(index);
            }

            /**
            * @brief Access element with bounds checking
            * @param index Element index
            * @return Reference to requested element
            * @throws std::out_of_range if index is outside the vector's dimensions
            **/
            [[nodiscard]] constexpr const T& at(std::size_t index) const {
                return m_data.at(index);
            }

            constexpr Vector() = default;

            /**
            * @brief Constructs a vector from an initializer list
            * Remaining elements are value initialized if fewer than D dimensions are provided
            * @param elements Vector elements
            * @throws std::invalid_argument if more than D elements are provided
            **/
            constexpr Vector(const std::initializer_list<T> elements) {
                if (elements.size() > D) [[unlikely]] {
                    throw std::invalid_argument("Parameters exceed provided dimensions");
                }

                for (std::size_t index{0}; const auto& element : elements) {
                    m_data[index] = element;
                    index++;
                }
            }


            constexpr Vector& operator+=(const Vector& other) noexcept {
                for (std::size_t index{0}; index < D; index++) {
                    m_data[index] += other[index];
                }
                return *this;
            }

            constexpr Vector& operator-=(const Vector& other) noexcept {
                for (std::size_t index{0}; index < D; index++) {
                    m_data[index] -= other[index];
                }
                return *this;
            }

            friend Vector operator+(Vector lhs, const Vector& rhs) noexcept {
                return lhs += rhs;
            }

            friend Vector operator-(Vector lhs, const Vector& rhs) noexcept {
                return lhs -= rhs;
            }

            /**
            * @brief Temporary utility function, will be omitted upon release
            * @param Vector Vector
            **/
            friend void show(const vektor::Vector<T, D>& vec) {
                for (const auto& each : vec.m_data) {
                    std::print("{} ", each);
                } 
                std::println();
            }

        };

    }

}