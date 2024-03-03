#pragma once

#define MIXIN_PROTECT(name)                                  \
        public:                                              \
            template <typename Children>                     \
            name(const Children&) = delete;                  \
        protected:                                           \
            name() = default;                                \
            ~name() = default;
// support ebo in msvc > c++14
#ifdef MSVC
    #define EBO __declspec(empty_bases)
#else
    #define EBO
#endif

/**
 * todo 1. support boost operator_left + support iterator  + compare  + groupMixin together
 */
namespace knight
{
    // @formatter:off
    //1.  when you inherate from Mixin Class , not mean is-a ; so delete copy construct
    //2.  Mixin Class can'b be use directly and use it to construct a object


    template <typename... T>
    struct EBO Mixin : public T...{ };

    #define KNIGHT_BINARY_OPERATOR(NAME, OP, COMMUTATIVETAG)                \
    namespace detail{                                                       \
        template <typename T,bool COMMUTATIVE = true>                       \
        struct NAME##Base{                                                  \
            template <typename Self>                                        \
            constexpr Self operator OP(this const Self& lhs, const T& rhs)  \
            { Self nrv(lhs); nrv OP##= (rhs); return nrv; }                 \
            template <typename Self>                                        \
            requires(COMMUTATIVE)                                           \
            constexpr friend Self operator OP(const T& lhs, const Self& rhs)\
            { Self nrv(rhs); nrv OP##= lhs; return nrv; }                   \
        };                                                                  \
    }                                                                       \
    template <typename... T>                                                \
    struct NAME : public knight::detail::NAME##Base<T,COMMUTATIVETAG>...    \
    {                                                                       \
        template <typename Self>                                            \
        constexpr Self operator OP(this const Self& lhs, const Self& rhs)   \
        { Self nrv(lhs); nrv OP##= (rhs); return nrv;                       \
        }                                                                   \
        using knight::detail::NAME##Base<T>::operator OP...;                \
        MIXIN_PROTECT(NAME)                                                 \
    };                                                                      \

    KNIGHT_BINARY_OPERATOR(AddMixin, + ,true)
    KNIGHT_BINARY_OPERATOR(MultipliMixin, * , true)

    KNIGHT_BINARY_OPERATOR(SubtractMixin, -, false)
    KNIGHT_BINARY_OPERATOR(DividMixin, /, false)
    KNIGHT_BINARY_OPERATOR(ModMixin, % ,false)

    KNIGHT_BINARY_OPERATOR(XorMixin, ^ , true)
    KNIGHT_BINARY_OPERATOR(AndMixin, &,true)
    KNIGHT_BINARY_OPERATOR(OrMixin, |,true)

    KNIGHT_BINARY_OPERATOR(left_shiftable, <<, false)
    KNIGHT_BINARY_OPERATOR(right_shiftable, >> ,false)
    #undef KNIGHT_BINARY_OPERATOR

    struct IncrementMix{
        constexpr auto operator++(this auto& self, int) {
            auto old_nrv(self); ++self; return old_nrv;
        }
        MIXIN_PROTECT(IncrementMix)
    };

    struct DecrementMix{
        constexpr auto operator--(this auto& self, int) {
            auto old_nrv(self); --self; return old_nrv;
        }
        MIXIN_PROTECT(DecrementMix)
    };
    // @formatter:on：这个注释告诉CLion在此处启用格式化。

    // template <class P>
    //    struct dereferenceable{
    //     template<typename Self>
    //     P operator->(this Self & self) const {
    //         return std::addressof(*static_cast<const Self&>(*this));
    //     }
    // };
    // template <class T, class I, class R>
    // struct indexable{
    //     R operator[](I n) const {
    //         return *(static_cast<const T&>(*this) + n);
    //     }
    // };

    //every group should use EBO for msvc

    template <typename... T>
    struct EBO operatorAll : public AddMixin<T...>, SubtractMixin<T...>, MultipliMixin<T...>, DividMixin<T...>{
        MIXIN_PROTECT(operatorAll)
    };

    template <typename... T>
    struct EBO bitWise : public AndMixin<T...>, OrMixin<T...>, XorMixin<T...>, left_shiftable<T...>, right_shiftable<T...>{
        MIXIN_PROTECT(bitWise)
    };

    struct EBO unit_steppable : public IncrementMix, DecrementMix{
        MIXIN_PROTECT(unit_steppable)
    };
    //todo support iterator
    // template <typename... T>
    // struct EBO iterator {
    //     MIXIN_PROTECT(iterator)
    // };
}

#undef EBO
#undef MIXIN_PROTECT
