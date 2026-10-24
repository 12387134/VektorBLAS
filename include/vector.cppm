export module vektor:vector;
import :types;
import std;

export namespace vektor {

    inline namespace naive {

        /**
        * @brief fixed-size mathematical vector
        * @tparam T The datatype of the vector
        * @tparam D The amount of dimensions of the vector
        * @return None
        **/
        template <typename T, std::size_t D>
        class Vector {
            private:
                std::array<T, D> m_data{};

            public:

            [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
                return m_data[index];
            }

            [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
                return m_data[index];
            }

            constexpr Vector() = default;

            // TODO: Refactor to use std::copy rather than a for loop, implement a second constructor using std::span instead of initializer list
            constexpr Vector(const std::initializer_list<T>& elements) {
                if (elements.size() > D) [[unlikely]] {
                    throw std::invalid_argument("Parameters exceed provided dimensions");
                }

                for (std::size_t index{0}; const auto& element : elements) {
                    m_data[index] = element;
                    index++;
                }
            }

            // TODO: Refactor mathematical operations to use std::transform rather than for loops

            [[nodiscard]] constexpr Vector operator+(const Vector& other) const {
                Vector result{};
                for (std::size_t index{0}; index < D; index++) {
                    result[index] = m_data[index] + other[index];
                }
                return result;
            }

            [[nodiscard]] constexpr Vector operator-(const Vector& other) const {
                Vector result{};
                for (std::size_t index{0}; index < D; index++) {
                    result[index] = m_data[index] - other[index];
                }
                return result;
            }

        };

    }

}