export module vektor:vector;
import :types;
import std;

export namespace vektor {

    template <typename T>
    concept vektor_numeric = (std::integral<T> || std::floating_point<T>) && !std::same_as<T, bool>;

    inline namespace naive {

        /**
        * @brief fixed-size mathematical vector
        * @tparam T The datatype of the vector
        * @tparam D The amount of dimensions of the vector
        **/
        template <vektor_numeric T, std::size_t D>
        class Vector {
            // * Catch invalid number of dimensions provided during compilation time
            static_assert(D > 0, "Dimensions must be greater than 0");

            private:
                std::array<T, D> m_data{};

            public:

            [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
                return m_data[index];
            }

            [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
                return m_data[index];
            }

            [[nodiscard]] constexpr T& at(std::size_t index) {
                return m_data.at(index);
            }

            [[nodiscard]] constexpr const T& at(std::size_t index) const {
                return m_data.at(index);
            }

            constexpr Vector() = default;

            constexpr Vector(const std::initializer_list<T>& elements) {
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

            // * Temporary utility function, will be omitted upon release
            friend void show(const vektor::Vector<T, D>& vec) {
                for (const auto& each : vec.m_data) {
                    std::print("{} ", each);
                } 
                std::println();
            }

        };

    }

}