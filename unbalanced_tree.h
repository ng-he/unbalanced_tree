
// |
// V
/*
                DAISAN NO BAKUDAN, BYTES ZA DUSTO :)))
*/

#pragma once
#ifndef _UNBALANCED_TREE_
#define _UNBALANCED_TREE_
#include <yvals_core.h>
#if _STL_COMPILER_PREPROCESSOR
#include <xmemory>
#include <vector>

#pragma pack(push, _CRT_PACKING)
#pragma warning(push, _STL_WARNING_LEVEL)
#pragma warning(disable : _STL_DISABLED_WARNINGS)
_STL_DISABLE_CLANG_WARNINGS
#pragma push_macro("new")
#undef new

// TEMPLATE CLASS _Utree_branch_const_iterator
template<class _Utree_iter>
class _Utree_branch_const_iterator { // iterator cho cac nhanh cua moi nut
public:
    using iterator_category = _STD random_access_iterator_tag;

    using _Nodeptr        = typename _Utree_iter::_Nodeptr;
    using _Bran_iter      = typename _STD vector<_Nodeptr>::const_iterator;
    using value_type      = typename _Bran_iter::value_type;
    using difference_type = typename _Bran_iter::difference_type;
    using pointer         = typename _Bran_iter::pointer;
    using reference       = typename _Bran_iter::reference;
    using branch_size_t   = typename _STD vector<_Nodeptr>::size_type;

    _Utree_branch_const_iterator(_Utree_iter _Root_, _Bran_iter _Bran_) : _Root(_Root_), _Bran(_Bran_) {
        _Root_check();
    }

    _Utree_branch_const_iterator(_Utree_iter _Root_, branch_size_t _Branpos) : _Root(_Root_) {
        _Bran = _Root._Ptr->branches.begin() + _Branpos;
    }

    _NODISCARD reference operator*() const {
        return _Bran.operator*();
    }

    _NODISCARD pointer operator->() const {
        return _Bran.operator->();
    }

    _Utree_branch_const_iterator& operator++() {
        ++_Bran;
        return *this;
    }

    _Utree_branch_const_iterator operator++(int) {
        _Utree_branch_const_iterator _Tmp = *this;
        ++*this;
        return _Tmp;
    }

    _Utree_branch_const_iterator& operator--() {
        --_Bran;
        return *this;
    }

    _Utree_branch_const_iterator operator--(int) {
        _Utree_branch_const_iterator _Tmp = *this;
        --*this;
        return _Tmp;
    }

    _Utree_branch_const_iterator& operator+=(const difference_type _Off) {
        _Bran += _Off;
        return *this;
    }

    _NODISCARD _Utree_branch_const_iterator operator+(const difference_type _Off) {
        _Utree_branch_const_iterator _Tmp = *this;
        return _Tmp += _Off;
    }

    _Utree_branch_const_iterator& operator-=(const difference_type _Off) {
        return *this += -_Off;
    }

    _NODISCARD _Utree_branch_const_iterator operator-(const difference_type _Off) {
        _Utree_branch_const_iterator _Tmp = *this;
        return _Tmp -= _Off;
    }

    _NODISCARD difference_type operator-(const _Utree_branch_const_iterator& _Right) const {
        return _Bran - _Right._Bran;
    }

    _NODISCARD reference operator[](const difference_type _Off) const {
        return *(*this + _Off);
    }

    _NODISCARD bool operator==(const _Utree_branch_const_iterator& _Right) const {
        _Root_compat(_Right);
        return _Bran == _Right._Bran;
    }

    _NODISCARD bool operator!=(const _Utree_branch_const_iterator& _Right) const {
        return !(*this == _Right);
    }

    _NODISCARD bool operator<(const _Utree_branch_const_iterator& _Right) const {
        return _Bran < _Right._Bran;
    }

    _NODISCARD bool operator>(const _Utree_branch_const_iterator& _Right) const {
        return _Right < *this;
    }

    _NODISCARD bool operator<=(const _Utree_branch_const_iterator& _Right) const {
        return !(_Right < *this);
    }

    _NODISCARD bool operator>=(const _Utree_branch_const_iterator& _Right) const {
        return !(*this < _Right);
    }

    void _Root_compat(const _Utree_branch_const_iterator& _Right) const {
        _STL_VERIFY(this->get_root() == _Right.get_root(), "branch iterators incompatible");
    }

    void _Root_check() const { // check if the branch has the correct root
#if _ITERATOR_DEBUG_LEVEL != 0
        const auto _Root_cont = _Root._Ptr->branches.begin()._Getcont();
        const auto _Bran_cont = _Bran._Getcont();
        _STL_VERIFY(_Root_cont == _Bran_cont, "branch belongs to another root");
#endif // _ITERATOR_DEBUG_LEVEL != 0   
    }

    const _Utree_iter get_root() const noexcept {
        return _Root;
    }

    _NODISCARD _Bran_iter get_branch() const noexcept {
        return _Bran;
    }

#if _ITERATOR_DEBUG_LEVEL != 0
    friend void _Verify_range(const _Utree_branch_const_iterator& _First, const _Utree_branch_const_iterator& _Last) {
        _STL_VERIFY(_First.get_root() == _Last.get_root(), "branch iterators in range are from different roots");
        _STL_VERIFY(_First <= _Last, "branch iterator range transposed");
    }
#endif // _ITERATOR_DEBUG_LEVEL != 0

    using _Prevent_inheriting_unwrap = _Utree_branch_const_iterator;

    _NODISCARD pointer _Unwrapped() const {
        return _Unfancy(_Bran._Ptr);
    }

    void _Seek_to(const _Utree_branch_const_iterator _It) {
        this->_Root = _It._Root;
        this->_Bran = _It._Bran;
    }

    _Utree_iter _Root; // iterator to the root of branch
    _Bran_iter _Bran; // branch iterator
};

template <class _Utree_iter, class _MyUtree>
_NODISCARD _Utree_branch_const_iterator<_Utree_iter> operator+(
    typename _Utree_branch_const_iterator<_Utree_iter>::difference_type _Off, _Utree_branch_const_iterator<_Utree_iter> _Next) {
    return _Next += _Off;
}

template<class _Utree_iter>
_NODISCARD constexpr typename _Utree_branch_const_iterator<_Utree_iter>::pointer _Get_unwrapped(_Utree_branch_const_iterator<_Utree_iter>&& _It) {
    return static_cast<_Utree_branch_const_iterator<_Utree_iter>&&>(_It)._Unwrapped();
}

// TEMPLATE CLASS _Utree_branch_iterator
template<class _Utree_iter>
class _Utree_branch_iterator : public _Utree_branch_const_iterator<_Utree_iter> {
public:
    using _Mybase           = _Utree_branch_const_iterator<_Utree_iter>;
    using iterator_category = _STD random_access_iterator_tag;

    using _Nodeptr        = typename _Utree_iter::_Nodeptr;
    using _Bran_iter      = typename _STD vector<_Nodeptr>::iterator;
    using value_type      = typename _Bran_iter::value_type;
    using difference_type = typename _Bran_iter::difference_type;
    using pointer         = typename _Bran_iter::pointer;
    using reference       = typename _Bran_iter::reference;
    using branch_size_t   = typename _STD vector<_Nodeptr>::size_type;

    using _Mybase::_Mybase;

    _NODISCARD reference operator*() const {
        return const_cast<reference>(_Mybase::operator*());
    }

    _NODISCARD pointer operator->() const {
        return _STD _Const_cast(_Mybase::operator->());
    }

    _Utree_branch_iterator& operator++() {
        _Mybase::operator++();
        return *this;
    }

    _Utree_branch_iterator operator++(int) {
        _Utree_branch_iterator _Tmp = *this;
        _Mybase::operator++();
        return _Tmp;
    }

    _Utree_branch_iterator& operator--() {
        _Mybase::operator--();
        return *this;
    }

    _Utree_branch_iterator operator--(int) {
        _Utree_branch_iterator _Tmp = *this;
        _Mybase::operator--();
        return _Tmp;
    }

    _Utree_branch_iterator& operator+=(const difference_type _Off) {
        _Mybase::operator+=(_Off);
        return *this;
    }

    _NODISCARD _Utree_branch_iterator operator+(const difference_type _Off) const {
        _Utree_branch_iterator _Tmp = *this;
        return _Tmp += _Off;
    }

    _Utree_branch_iterator& operator-=(const difference_type _Off) {
        _Mybase::operator-=(_Off);
        return *this;
    }

    using _Mybase::operator-;

    _NODISCARD _Utree_branch_iterator operator-(const difference_type _Off) const {
        _Utree_branch_iterator _Tmp = *this;
        return _Tmp -= _Off;
    }

    _NODISCARD reference operator[](const difference_type _Off) const {
        return const_cast<reference>(_Mybase::operator[](_Off));
    }

    _NODISCARD _Bran_iter get_branch() noexcept {
        return _Bran_iter(this->_Bran._Ptr, this->_Bran._Getcont());
    }

    using _Prevent_inheriting_unwrap = _Utree_branch_iterator;

    _NODISCARD pointer _Unwrapped() const {
        return _Unfancy(this->_Bran._Ptr);
    }
};

template <class _Utree_iter, class _MyUtree>
_NODISCARD _Utree_branch_iterator<_Utree_iter> operator+(
    typename _Utree_branch_iterator<_Utree_iter>::difference_type _Off, _Utree_branch_iterator<_Utree_iter> _Next) {
    return _Next += _Off;
}

template<class _Utree_iter>
_NODISCARD constexpr typename _Utree_branch_iterator<_Utree_iter>::pointer _Get_unwrapped(_Utree_branch_iterator<_Utree_iter>&& _It) {
    return static_cast<_Utree_branch_iterator<_Utree_iter>&&>(_It)._Unwrapped();
}

// TEMPLATE CLASS _Utree_unchecked_const_iterator  
template<class _MyUtree, class _Base = _STD _Iterator_base0>
class _Utree_unchecked_const_iterator : public _Base {
public:
	using iterator_category = _STD bidirectional_iterator_tag;

    using _Nodeptr        = typename _MyUtree::_Nodeptr;
    using value_type      = typename _MyUtree::value_type;
    using difference_type = typename _MyUtree::difference_type;
    using pointer         = typename _MyUtree::const_pointer;
    using reference       = const value_type&;
    using branch_size_t   = typename _MyUtree::branch_size_t;

    using branch_iterator               = _Utree_branch_iterator<_Utree_unchecked_const_iterator>;
    using branch_const_iterator         = _Utree_branch_const_iterator<_Utree_unchecked_const_iterator>;
    using branch_reverse_iterator       = _STD reverse_iterator<branch_iterator>;
    using branch_const_reverse_iterator = _STD reverse_iterator<branch_const_iterator>;

    _Utree_unchecked_const_iterator() noexcept : _Ptr() {};

    _Utree_unchecked_const_iterator(_Nodeptr _Pnode, const _MyUtree* _PUtree) noexcept : _Ptr(_Pnode) {
        this->_Adopt(_PUtree);
    }

    _NODISCARD reference operator*() const {
        return _Ptr->_Myval;
    }

    _NODISCARD pointer operator->() const {
        return _STD pointer_traits<pointer>::pointer_to(**this);
    }

    _Utree_unchecked_const_iterator& operator++() {
        if (_Ptr->branches.size() == 0) { // neu la nut la
            while (_Ptr->branpos == _Ptr->parent->branches.size() - 1) {
                _Ptr = _Ptr->parent; // ==> la nhanh cuoi cung cua parent ==> parent
            }
            _Ptr = _Ptr->parent->branches[_Ptr->branpos + 1]; // ==> nhanh tiep theo
        } else {
            _Ptr = _Ptr->branches[0]; // ==> tro den nhanh dau tien
        }
        return *this;
    }

    _Utree_unchecked_const_iterator operator++(int) {
        _Utree_unchecked_const_iterator _Tmp = *this;
        ++*this;
        return _Tmp;
    }

    _Utree_unchecked_const_iterator& operator--() {
        if (_Ptr->branpos == 0) { // la nhanh dau tien cua parent
            _Ptr = _Ptr->parent; // ==> parent
        } else {
            _Ptr = _Ptr->parent->branches[_Ptr->branpos - 1]; // quay lai nhanh truoc do cua parent
            while (_Ptr->branches.size() != 0) {
                _Ptr = _Ptr->branches.back(); // tro den nhanh cuoi cung cho den khi la nut la
            }
        }
        return *this;
    }

    _Utree_unchecked_const_iterator operator--(int) {
        _Utree_unchecked_const_iterator _Tmp = *this;
        --*this;
        return _Tmp;
    }

    _NODISCARD bool operator==(const _Utree_unchecked_const_iterator& _Right) const {
        return _Ptr == _Right._Ptr;
    }

    _NODISCARD bool operator!=(const _Utree_unchecked_const_iterator& _Right) const {
        return !(*this == _Right);
    }

    template<class _Iter, _STD enable_if_t<_STD is_integral_v<_STD _Iter_value_t<_Iter>>, int> = 0>
    _Utree_unchecked_const_iterator& _To_branch_unchecked(_Iter _First, _Iter _Last) { 
        // di chuyen iterator qua tung vi tri nhanh trong [_First, _Last) 
        auto _UFirst = _STD _Get_unwrapped(_First);
        auto _ULast  = _STD _Get_unwrapped(_Last);
        _STD _Adl_verify_range(_UFirst, _ULast);

        while (_UFirst != _ULast) {
            _Ptr = _Ptr->branches[static_cast<branch_size_t>(*_UFirst)];
            _UFirst++;
        }
        return *this;
    }

    _Utree_unchecked_const_iterator& _To_branch_unchecked(_STD initializer_list<branch_size_t> _Iloc) {
        return _To_branch_unchecked(_Iloc.begin(), _Iloc.end());
    }

    _Utree_unchecked_const_iterator& _To_parent_unchecked(size_t _Off = 1) {
        // di chuyen iterator den parent thu off
        while (_Off != 0) {
            _Ptr = _Ptr->parent;
            _Off--;
        }
        return *this;
    }

    _NODISCARD branch_iterator operator[](branch_size_t _Branpos) noexcept { 
        return branch_iterator(*this, _Branpos);
    }

    _NODISCARD branch_const_iterator operator[](branch_size_t _Branpos) const noexcept {
        return branch_const_iterator(*this, _Branpos);
    }

    _NODISCARD branch_iterator bran_at(branch_size_t _Branpos) noexcept {
        return branch_iterator(*this, _Branpos);
    }

    _NODISCARD branch_const_iterator bran_at(branch_size_t _Branpos) const noexcept {
        return branch_const_iterator(*this, _Branpos);
    }

    _NODISCARD branch_iterator bran_begin() noexcept {
        return branch_iterator(*this, _Ptr->branches.begin());
    }

    _NODISCARD branch_const_iterator bran_begin() const noexcept {
        return branch_const_iterator(*this, _Ptr->branches.begin());
    }

    _NODISCARD branch_iterator bran_end() noexcept {
        return branch_iterator(*this, _Ptr->branches.end());
    }

    _NODISCARD branch_const_iterator bran_end() const noexcept {
        return branch_const_iterator(*this, _Ptr->branches.end());
    }

    _NODISCARD branch_reverse_iterator bran_rbegin() noexcept {
        return branch_reverse_iterator(bran_end());
    }

    _NODISCARD branch_const_reverse_iterator bran_rbegin() const noexcept {
        return branch_const_reverse_iterator(bran_end());
    }

    _NODISCARD branch_reverse_iterator bran_rend() noexcept {
        return branch_reverse_iterator(bran_begin());
    }

    _NODISCARD branch_const_reverse_iterator bran_rend() const noexcept {
        return branch_const_reverse_iterator(bran_begin());
    }

    _NODISCARD branch_const_iterator bran_cbegin() const noexcept {
        return bran_begin();
    }

    _NODISCARD branch_const_iterator bran_cend() const noexcept {
        return bran_end();
    }

    _NODISCARD branch_const_reverse_iterator bran_crbegin() const noexcept {
        return bran_rbegin();
    }

    _NODISCARD branch_const_reverse_iterator bran_crend() const noexcept {
        return bran_rend();
    }

    _NODISCARD branch_size_t bran_size() const noexcept {
        return _Ptr->branches.size();
    }
    
public:
    _Nodeptr _Ptr; // pointer den nut;
};

// TEMPLATE CLASS _Utree_unchecked_iterator
template<class _MyUtree>
class _Utree_unchecked_iterator : public _Utree_unchecked_const_iterator<_MyUtree> {
public:
    using _Mybase           = _Utree_unchecked_const_iterator<_MyUtree>;
    using iterator_category = _STD bidirectional_iterator_tag;

    using _Nodeptr        = typename _MyUtree::_Nodeptr;
    using value_type      = typename _MyUtree::value_type;
    using difference_type = typename _MyUtree::difference_type;
    using pointer         = typename _MyUtree::const_pointer;
    using reference       = value_type&;
    using branch_size_t   = typename _MyUtree::branch_size_t;

    using branch_iterator               = _Utree_branch_iterator<_Utree_unchecked_iterator>;
    using branch_const_iterator         = _Utree_branch_const_iterator<_Utree_unchecked_iterator>;
    using branch_reverse_iterator       = _STD reverse_iterator<branch_iterator>;
    using branch_const_reverse_iterator = _STD reverse_iterator<branch_const_iterator>;

    using _Mybase::_Mybase;

    _NODISCARD reference operator*() const {
        return const_cast<reference>(_Mybase::operator*());
    }

    _NODISCARD pointer operator->() const {
        return _STD pointer_traits<pointer>::pointer_to(**this);
    }

    _Utree_unchecked_iterator& operator++() {
        _Mybase::operator++();
        return *this;
    }

    _Utree_unchecked_iterator operator++(int) {
        _Utree_unchecked_iterator _Tmp = *this;
        _Mybase::operator++();
        return _Tmp;
    }

    _Utree_unchecked_iterator& operator--() {
        _Mybase::operator--();
        return *this;
    }

    _Utree_unchecked_iterator operator--(int) {
        _Utree_unchecked_iterator _Tmp = *this;
        _Mybase::operator--();
        return _Tmp;
    }

    _NODISCARD branch_iterator operator[](branch_size_t _Branpos) noexcept {
        return branch_iterator(*this, _Branpos);
    }

    _NODISCARD branch_const_iterator operator[](branch_size_t _Branpos) const noexcept {
        return branch_const_iterator(*this, _Branpos);
    }

    _NODISCARD branch_iterator bran_at(branch_size_t _Branpos) noexcept {
        return branch_iterator(*this, _Branpos);
    }

    _NODISCARD branch_const_iterator bran_at(branch_size_t _Branpos) const noexcept {
        return branch_const_iterator(*this, _Branpos);
    }

    _NODISCARD branch_iterator bran_begin() noexcept {
        return branch_iterator(*this, this->_Ptr->branches.begin());
    }

    _NODISCARD branch_const_iterator bran_begin() const noexcept {
        return branch_const_iterator(*this, this->_Ptr->branches.begin());
    }

    _NODISCARD branch_iterator bran_end() noexcept {
        return branch_iterator(*this, this->_Ptr->branches.end());
    }

    _NODISCARD branch_const_iterator bran_end() const noexcept {
        return branch_const_iterator(*this, this->_Ptr->branches.end());
    }

    _NODISCARD branch_reverse_iterator bran_rbegin() noexcept {
        return branch_reverse_iterator(bran_end());
    }

    _NODISCARD branch_const_reverse_iterator bran_rbegin() const noexcept {
        return branch_const_reverse_iterator(bran_end());
    }

    _NODISCARD branch_reverse_iterator bran_rend() noexcept {
        return branch_reverse_iterator(bran_begin());
    }

    _NODISCARD branch_const_reverse_iterator bran_rend() const noexcept {
        return branch_const_reverse_iterator(bran_begin());
    }

    _NODISCARD branch_const_iterator bran_cbegin() const noexcept {
        return bran_begin();
    }

    _NODISCARD branch_const_iterator bran_cend() const noexcept {
        return bran_end();
    }

    _NODISCARD branch_const_reverse_iterator bran_crbegin() const noexcept {
        return bran_rbegin();
    }

    _NODISCARD branch_const_reverse_iterator bran_crend() const noexcept {
        return bran_rend();
    }
};

// TEMPLATE CLASS _Utree_const_iterator
template<class _MyUtree>
class _Utree_const_iterator : public _Utree_unchecked_const_iterator<_MyUtree, _STD _Iterator_base> {
public:
    using _Mybase           = _Utree_unchecked_const_iterator<_MyUtree, _STD _Iterator_base>;
    using iterator_category = _STD bidirectional_iterator_tag;

    using _Nodeptr        = typename _MyUtree::_Nodeptr;
    using value_type      = typename _MyUtree::value_type;
    using difference_type = typename _MyUtree::difference_type;
    using pointer         = typename _MyUtree::const_pointer;
    using reference       = const value_type&;
    using branch_size_t   = typename _MyUtree::branch_size_t;

    using branch_iterator               = _Utree_branch_iterator<_Utree_const_iterator>;
    using branch_const_iterator         = _Utree_branch_const_iterator<_Utree_const_iterator>;
    using branch_reverse_iterator       = _STD reverse_iterator<branch_iterator>;
    using branch_const_reverse_iterator = _STD reverse_iterator<branch_const_iterator>;

    using _Mybase::_Mybase;

    _NODISCARD reference operator*() const {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());        
        _STL_ASSERT(this->_Getcont(), "cannot dereference value-initialized unbalanced tree iterator");
        _STL_VERIFY(this->_Ptr != _Mycont->_Myroot, "cannot dereference root unbalanced tree iterator");
        _STL_VERIFY(this->_Ptr != _Mycont->_Myend, "cannot dereference end unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return this->_Ptr->_Myval;
    }

    _NODISCARD pointer operator->() const {
        return _STD pointer_traits<pointer>::pointer_to(**this);
    }

    _Utree_const_iterator& operator++() {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(this->_Getcont(), "cannot dereference value-initialized unbalanced tree iterator");
        _STL_VERIFY(this->_Ptr != _Mycont->_Myend, "cannot increment end unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        _Mybase::operator++();
        return *this;
    }

    _Utree_const_iterator operator++(int) {
        _Utree_const_iterator _Tmp = *this;
        ++*this;
        return _Tmp;
    }

    _Utree_const_iterator& operator--() {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont()); 
        _STL_ASSERT(this->_Getcont(), "cannot dereference value-initialized unbalanced tree iterator"); 
        _STL_VERIFY(this->_Ptr != _Mycont->_Myroot, "cannot decrement root unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        _Mybase::operator--();
        return *this;
    }

    _Utree_const_iterator operator--(int) {
        _Utree_const_iterator _Tmp = *this;
        --*this;
        return _Tmp;
    }

    _NODISCARD bool operator==(const _Utree_const_iterator& _Right) const {
        _Compat(_Right);
        return this->_Ptr == _Right._Ptr;
    }

    _NODISCARD bool operator!=(const _Utree_const_iterator& _Right) const {
        return !(*this == _Right);
    }

    void _Compat(const _Utree_const_iterator& _Right) const { // kiem tra cap iterator co cung 1 container khong
#if _ITERATOR_DEBUG_LEVEL == 0
        (void)_Right;
#else // ^^^ _ITERATOR_DEBUG_LEVEL == 0 ^^^ // vvv _ITERATOR_DEBUG_LEVEL != 0 vvv
        _STL_VERIFY(this->_Getcont() == _Right._Getcont(), "unbalanced tree iterators incompatible");
#endif // _ITERATOR_DEBUG_LEVEL == 0
    }

    template<class _Iter, enable_if_t<is_integral_v<_Iter_value_t<_Iter>>, int> = 0>
    _Utree_const_iterator& to_branch(_Iter _First, _Iter _Last) {
        // di chuyen iterator qua tung vi tri nhanh trong [_First, _Last) 
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator"); 
#endif // _ITERATOR_DEBUG_LEVEL == 2

        auto _UFirst = _STD _Get_unwrapped(_First);
        auto _ULast  = _STD _Get_unwrapped(_Last);
        _STD _Adl_verify_range(_UFirst, _ULast);

        while (_UFirst != _ULast) {
#if _ITERATOR_DEBUG_LEVEL == 2
            _STL_VERIFY(this->_Ptr->branches.size() != 0, "cannot move after leaf");
            _STL_VERIFY(
                static_cast<branch_size_t>(*_UFirst) < this->_Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

            this->_Ptr = this->_Ptr->branches[static_cast<branch_size_t>(*_UFirst)];
            ++_UFirst;
        }
        return *this;
    }

    _Utree_const_iterator& to_branch(_STD initializer_list<branch_size_t> _Iloc) {
        return to_branch(_Iloc.begin(), _Iloc.end());
    }

    _Utree_const_iterator& to_parent(size_t _Off) {
        // di chuyen iterator den parent thu _Off
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator"); 
#endif // _ITERATOR_DEBUG_LEVEL == 2

        while (_Off != 0) {
#if _ITERATOR_DEBUG_LEVEL == 2
            _STL_VERIFY(this->_Ptr != _Mycont->_Myroot, "cannot move before root unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2
            this->_Ptr = this->_Ptr->parent;
            --_Off;
        }
        return *this;
    }

#if _ITERATOR_DEBUG_LEVEL == 2
    friend void _Verify_range(const _Utree_const_iterator& _First, const _Utree_const_iterator& _Last) {
        _STL_VERIFY(_First._Getcont() == _Last._Getcont(), "unbalanced tree iterators in range are from different containers");
    }
#endif // _ITERATOR_DEBUG_LEVEL == 2

    using _Prevent_inheriting_unwrap = _Utree_const_iterator;

    _NODISCARD _Utree_unchecked_const_iterator<_MyUtree> _Unwrapped() const {
        return _Utree_unchecked_const_iterator<_MyUtree>(this->_Ptr, static_cast<const _MyUtree*>(this->_Getcont()));
    }

    void _Seek_to(const _Utree_unchecked_const_iterator<_MyUtree> _It) {
        this->_Ptr = _It._Ptr;
    }

    _NODISCARD branch_iterator operator[](branch_size_t _Branpos) noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
        _STL_VERIFY(_Branpos <= this->_Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_iterator(*this, _Branpos);
    }

    _NODISCARD branch_const_iterator operator[](branch_size_t _Branpos) const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
        _STL_VERIFY(_Branpos <= this->_Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_const_iterator(*this, _Branpos);
    }

    _NODISCARD branch_iterator bran_at(branch_size_t _Branpos) noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
        _STL_VERIFY(_Branpos <= this->_Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_iterator(*this, _Branpos);
    }

    _NODISCARD branch_const_iterator bran_at(branch_size_t _Branpos) const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
        _STL_VERIFY(_Branpos <= this->_Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL ==

        return branch_const_iterator(*this, _Branpos);
    }

    _NODISCARD branch_iterator bran_begin() noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_iterator(*this, this->_Ptr->branches.begin());
    }

    _NODISCARD branch_const_iterator bran_begin() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_const_iterator(*this, this->_Ptr->branches.begin());
    }

    _NODISCARD branch_iterator bran_end() noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_iterator(*this, this->_Ptr->branches.end());
    }

    _NODISCARD branch_const_iterator bran_end() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_const_iterator(*this, this->_Ptr->branches.end());
    }

    _NODISCARD branch_reverse_iterator bran_rbegin() noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_reverse_iterator(bran_end());
    }

    _NODISCARD branch_const_reverse_iterator bran_rbegin() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_const_reverse_iterator(bran_end());
    }

    _NODISCARD branch_reverse_iterator bran_rend() noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_reverse_iterator(bran_begin());
    }

    _NODISCARD branch_const_reverse_iterator bran_rend() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_const_reverse_iterator(bran_begin());
    }

    _NODISCARD branch_const_iterator bran_cbegin() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return bran_begin();
    }

    _NODISCARD branch_const_iterator bran_cend() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return bran_end();
    }

    _NODISCARD branch_const_reverse_iterator bran_crbegin() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return bran_rbegin();
    }

    _NODISCARD branch_const_reverse_iterator bran_crend() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return bran_rend();
    }
};

// TEMPLATE CLASS _Utree_iterator
template<class _MyUtree>
class _Utree_iterator : public _Utree_const_iterator<_MyUtree> {
public:
    using _Mybase           = _Utree_const_iterator<_MyUtree>;
    using iterator_category = _STD bidirectional_iterator_tag;

    using _Nodeptr        = typename _MyUtree::_Nodeptr;
    using value_type      = typename _MyUtree::value_type;
    using difference_type = typename _MyUtree::difference_type;
    using pointer         = typename _MyUtree::const_pointer;
    using reference       = value_type&;
    using branch_size_t   = typename _MyUtree::branch_size_t;

    using branch_iterator               = _Utree_branch_iterator<_Utree_iterator>;
    using branch_const_iterator         = _Utree_branch_const_iterator<_Utree_iterator>;
    using branch_reverse_iterator       = _STD reverse_iterator<branch_iterator>;
    using branch_const_reverse_iterator = _STD reverse_iterator<branch_const_iterator>;

    using _Mybase::_Mybase;

    _NODISCARD reference operator*() const {
        return const_cast<reference>(_Mybase::operator*());
    }

    _NODISCARD pointer operator->() const {
        return _STD pointer_traits<pointer>::pointer_to(**this);
    }

    _Utree_iterator& operator++() {
        _Mybase::operator++();
        return *this;
    }

    _Utree_iterator operator++(int) {
        _Utree_iterator _Tmp = *this;
        _Mybase::operator++();
        return _Tmp;
    }

    _Utree_iterator& operator--() {
        _Mybase::operator--();
        return *this;
    }

    _Utree_iterator operator--(int) {
        _Utree_iterator _Tmp = *this;
        _Mybase::operator--();
        return _Tmp;
    }

    template<class _Iter, _STD enable_if_t<_STD is_integral_v<_STD _Iter_value_t<_Iter>>, int> = 0>
    _Utree_iterator& to_branch(_Iter _First, _Iter _Last) {
        _Mybase::to_branch(_First, _Last);
        return *this;
    }

    _Utree_iterator& to_branch(_STD initializer_list<branch_size_t> _Iloc) {
        return to_branch(_Iloc.begin(), _Iloc.end());
    }

    _Utree_iterator& to_parent(size_t _Off) {
        _Mybase::to_parent(_Off);
        return *this;
    }

    using _Prevent_inheriting_unwrap = _Utree_iterator;

    _NODISCARD _Utree_unchecked_iterator<_MyUtree> _Unwrapped() const {
        return _Utree_unchecked_iterator<_MyUtree>(this->_Ptr, static_cast<const _MyUtree*>(this->_Getcont()));
    }

    _NODISCARD branch_iterator operator[](branch_size_t _Branpos) noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
        _STL_VERIFY(_Branpos <= this->_Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_iterator(*this, _Branpos);
    }

    _NODISCARD branch_const_iterator operator[](branch_size_t _Branpos) const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
        _STL_VERIFY(_Branpos <= this->_Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_const_iterator(*this, _Branpos);
    }

    _NODISCARD branch_iterator bran_at(branch_size_t _Branpos) noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
        _STL_VERIFY(_Branpos <= this->_Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_iterator(*this, _Branpos);
    }

    _NODISCARD branch_const_iterator bran_at(branch_size_t _Branpos) const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
        _STL_VERIFY(_Branpos <= this->_Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL ==

        return branch_const_iterator(*this, _Branpos);
    }

    _NODISCARD branch_iterator bran_begin() noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2
 
        return branch_iterator(*this, this->_Ptr->branches.begin());
    }

    _NODISCARD branch_const_iterator bran_begin() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_const_iterator(*this, this->_Ptr->branches.begin());
    }

    _NODISCARD branch_iterator bran_end() noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_iterator(*this, this->_Ptr->branches.end());
    }

    _NODISCARD branch_const_iterator bran_end() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_const_iterator(*this, this->_Ptr->branches.end());
    }

    _NODISCARD branch_reverse_iterator bran_rbegin() noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_reverse_iterator(bran_end());
    }

    _NODISCARD branch_const_reverse_iterator bran_rbegin() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_const_reverse_iterator(bran_end());
    }

    _NODISCARD branch_reverse_iterator bran_rend() noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_reverse_iterator(bran_begin());
    }

    _NODISCARD branch_const_reverse_iterator bran_rend() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return branch_const_reverse_iterator(bran_begin());
    }

    _NODISCARD branch_const_iterator bran_cbegin() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return bran_begin();
    }

    _NODISCARD branch_const_iterator bran_cend() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return bran_end();
    }

    _NODISCARD branch_const_reverse_iterator bran_crbegin() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return bran_rbegin();
    }

    _NODISCARD branch_const_reverse_iterator bran_crend() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
        const auto _Mycont = static_cast<const _MyUtree*>(this->_Getcont());
        _STL_ASSERT(_Mycont, "cannot dereference value-initialized unbalanced tree iterator");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return bran_rend();
    }
};

template<class _Iter, class _MyUtree>
_INLINE_VAR constexpr bool _Is_utree_iter = _STD _Is_any_of_v<
    _Iter, _Utree_unchecked_const_iterator<_MyUtree>, _Utree_unchecked_iterator<_MyUtree>,
    _Utree_const_iterator<_MyUtree>, _Utree_iterator<_MyUtree>>;

// unbalanced tree TYPE WRAPPERS
template <class _Value_type, class _Size_type, class _Difference_type, class _Pointer, class _Const_pointer,
    class _Reference, class _Const_reference, class _Nodeptr_type>
struct _Utree_iter_types {
    using value_type      = _Value_type;
    using size_type       = _Size_type;
    using difference_type = _Difference_type;
    using pointer         = _Pointer;
    using const_pointer   = _Const_pointer;
    using _Nodeptr        = _Nodeptr_type;
};

template<class _Value_type, class _Voidptr>
struct _Utree_node { // nut cua cay khong can bang
    using value_type    = _Value_type; 
    using _Nodeptr      = _STD _Rebind_pointer_t<_Voidptr, _Utree_node>;
    using _Bran_cont    = _STD vector<_Nodeptr>;
    using branch_size_t = typename _STD vector<_Nodeptr>::size_type;
    _Nodeptr parent; // parent (tro den nut cha), tro lai ve chinh no neu la goc 
    _Bran_cont branches; // vector cua con tro nut de lien ket cac cay con, khong dung neu la leaf hoac end
                         // doi voi nut cha cua end: duoc coi la mot nut la nen co the coi begin() va end() cua branches la trung nhau
    _Value_type _Myval; // luu tru gia tri, khong dung neu la root hoac end
    branch_size_t branpos; // luu tru vi tri nhanh doi voi parent, khong dung neu la root, luon luon la 0 neu end

    _Utree_node(const _Utree_node&) = delete;
    _Utree_node& operator=(const _Utree_node&) = delete;

    template<class _Alloc>
    static _Nodeptr _Buyroot(_Alloc& _Al, _CRT_GUARDOVERFLOW branch_size_t _Bransize = 1) { // tao nut root
        static_assert(_STD is_same_v<typename _Alloc::value_type, _Utree_node>, "Bad _Buyroot call");
        const auto _Pnode = _Al.allocate(1);
        _STD _Construct_in_place(_Pnode->parent, _Pnode);
        _STD _Construct_in_place(_Pnode->branches, _Bran_cont(_Bransize));
        for (_Nodeptr& _Bran : _Pnode->branches) {
            _Bran = NULL;
        }
        return _Pnode;
    }

    template<class _Alloc>
    static _Nodeptr _Buyend(_Alloc& _Al) { // tao nut end
        static_assert(_STD is_same_v<typename _Alloc::value_type, _Utree_node>, "Bad _Buyend call");
        const auto _Pnode = _Al.allocate(1);
        _Construct_in_place(_Pnode->parent, _Pnode);
        _Construct_in_place(_Pnode->branches, _Bran_cont(0));
        _Pnode->branpos = 0;
        return _Pnode;
    }

    template<class _Alloc, class... _Valty>
    static _Nodeptr _Buynode(_Alloc& _Al, _Nodeptr _Myroot, _CRT_GUARDOVERFLOW branch_size_t _Bransize, _Valty&&... _Val) {
        // cap phat 1 nut moi 
        static_assert(_STD is_same_v<typename _Alloc::value_type, _Utree_node>, "Bad _Buynode call");
        _STD _Alloc_construct_ptr<_Alloc> _Newnode(_Al);
        _Newnode._Allocate();
        _STD allocator_traits<_Alloc>::construct(_Al, _STD addressof(_Newnode._Ptr->_Myval), _STD forward<_Valty>(_Val)...);
        _STD _Construct_in_place(_Newnode._Ptr->parent, _Myroot);
        _STD _Construct_in_place(_Newnode._Ptr->branches, _Bran_cont(_Bransize));
        for (_Nodeptr& _Bran : _Newnode._Ptr->branches) {
            _Bran = NULL;
        }
        _Newnode._Ptr->branpos = 0;
        return _Newnode._Release();
    }

    template<class _Alloc>
    static void _Freenode0(_Alloc& _Al, _Nodeptr _Ptr) noexcept {
        // giai phong nut
        static_assert(_STD is_same_v<typename _Alloc::value_type, _Utree_node>, "Bad _Freenode0 call");
        for (size_t _Idx = 0; _Idx < _Ptr->branches.size(); ++_Idx) {
            _Ptr->branches[_Idx] = NULL;
        }
        _STD _Destroy_in_place(_Ptr->parent);
        _STD _Destroy_in_place(_Ptr->branches);
        _STD allocator_traits<_Alloc>::deallocate(_Al, _Ptr, 1);
    }

    template <class _Alloc>
    static void _Freenode(_Alloc& _Al, _Nodeptr _Ptr) noexcept {
        // giai phong nut va gia tri
        static_assert(_STD is_same_v<typename _Alloc::value_type, _Utree_node>, "Bad _Freenode call");
        _STD allocator_traits<_Alloc>::destroy(_Al, _STD addressof(_Ptr->_Myval));
        _Freenode0(_Al, _Ptr);
    }
};

template<class _Ty>
struct _Utree_simple_types : _STD _Simple_types<_Ty> {
    using _Node    = _Utree_node<_Ty, void*>;
    using _Nodeptr = _Node*;
};

template<class _Val_types>
class _Utree_val : public _STD _Container_base {
public:
    using _Nodeptr = typename _Val_types::_Nodeptr;

    using value_type      = typename _Val_types::value_type;
    using size_type       = typename _Val_types::size_type;
    using difference_type = typename _Val_types::difference_type;
    using pointer         = typename _Val_types::pointer;
    using const_pointer   = typename _Val_types::const_pointer;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using branch_size_t   = typename _STD vector<_Nodeptr>::size_type;

    using _Unchecked_const_iterator = _Utree_unchecked_const_iterator<_Utree_val>;
    using const_iterator            = _Utree_const_iterator<_Utree_val>;

    _Utree_val() noexcept : _Myroot(), _Myend(), _Mysize(0) {}

    void _Orphan_ptr(const _Nodeptr _Ptr) noexcept { // giai phong iterator 
#if _ITERATOR_DEBUG_LEVEL == 2
        _STD _Lockit _Lock(_LOCK_DEBUG);
        _STD _Iterator_base12** _Pnext = &this->_Myproxy->_Myfirstiter;
        while (*_Pnext) {
            const auto _Pnextptr = static_cast<const_iterator&>(**_Pnext)._Ptr;
            if (_Pnextptr == _Myroot || _Pnextptr == _Myend || (_Ptr != nullptr && _Pnextptr != _Ptr)) {
                _Pnext = &(*_Pnext)->_Mynextiter; // neu con tro cua iter khac _Ptr, skip
            } else { //  giai phong iterator 
                (*_Pnext)->_Myproxy = nullptr;
                *_Pnext             = (*_Pnext)->_Mynextiter;
            }
        }
#else // ^^^ _ITERATOR_DEBUG_LEVEL == 2 ^^^ // vvv _ITERATOR_DEBUG_LEVEL != 2 vvv
        (void)_Ptr;
#endif // _ITERATOR_DEBUG_LEVEL == 2
    }

    void _Adopt_all(_Utree_val& _Other) noexcept {
        // chuyen tat ca iter cua _Other cho *this (tru _Other.end() va _Other.root())
#if _ITERATOR_DEBUG_LEVEL == 2
        _STD _Lockit _Lock(_LOCK_DEBUG);
        _STD _Iterator_base12** _Pnext = &_Other._Myproxy->_Myfirstiter;
        const auto _Myproxy       = this->_Myproxy;
        while (*_Pnext) {
            auto& _Iter = static_cast<const_iterator&>(**_Pnext);
            if (_Iter._Ptr != _Other._Myroot || _Iter._Ptr != _Other._Myend) { // chuyen iter
                *_Pnext                = _Iter._Mynextiter;
                _Iter._Myproxy         = _Myproxy;
                _Iter._Mynextiter      = _Myproxy->_Myfirstiter;
                _Myproxy->_Myfirstiter = _STD addressof(_Iter);
            } else { // skip
                _Pnext = &_Iter._Mynextiter;
            }
        }
#endif // _ITERATOR_DEBUG_LEVEL == 2
    }

    void _Orphan_except_root_end() noexcept {
        // giai phong tat ca iter (tru root va end)
#if _ITERATOR_DEBUG_LEVEL == 2
        _STD _Lockit _Lock(_LOCK_DEBUG);
        _STD _Iterator_base12** _Pnext = &this->_Myproxy->_Myfirstiter;
        while (*_Pnext) {
            auto& _Iter = static_cast<const_iterator&>(**_Pnext);
            if (_Iter._Ptr == _Myroot || _Iter._Ptr == _Myend) { 
                *_Pnext = (*_Pnext)->_Mynextiter; // skip
            } else {  // giai phong iter
                (*_Pnext)->_Myproxy = nullptr;
                *_Pnext             = (*_Pnext)->_Mynextiter;
            }
        }

#endif // _ITERATOR_DEBUG_LEVEL == 2
    }

    void _Adopt_ptr(_Utree_val& _Other, const _Nodeptr _Pnode) noexcept {
        // chuyen iter thuoc _Other cho *this neu co con tro nut = _Pnode
#if _ITERATOR_DEBUG_LEVEL == 2
        _STD _Lockit _Lock(_LOCK_DEBUG);
        _STD _Iterator_base12** _Pnext = &_Other._Myproxy->_Myfirstiter;
        const auto _Myproxy       = this->_Myproxy;
        while (*_Pnext) {
            auto& _Iter = static_cast<const_iterator&>(**_Pnext);
            if (_Iter._Ptr == _Pnode) { // chuyen
                *_Pnext                = _Iter._Mynextiter;
                _Iter._Myproxy         = _Myproxy;
                _Iter._Mynextiter      = _Myproxy->_Myfirstiter;
                _Myproxy->_Myfirstiter = _STD addressof(_Iter);               
            } else { // skip
                _Pnext = &_Iter._Mynextiter;
            }
        }
#endif // _ITERATOR_DEBUG_LEVEL == 2
    }

    void _Branch_change_pos(_Nodeptr _Root) { // thay doi branpos cua cac nhanh cua _Root
        for (branch_size_t _Idx = 0; _Idx < _Root->branches.size(); ++_Idx) {
            _Root->branches[_Idx]->branpos = _Idx;
        }
    }

    void _To_new_end() { // tim nut la cuoi cung 
        _Nodeptr _New_parent = _Myroot;
        _Nodeptr _Old_parent = _Myend->parent;

        while (_New_parent->branches.size() != 0) {
            _New_parent = _New_parent->branches.back();
        }
        if (_New_parent == _Myend) {
            return;
        } else {
            if (_Old_parent) { 
                _Old_parent->branches[0] = NULL;
                _Old_parent->branches.clear();
            }
            _Myend->parent = _New_parent;       
            _New_parent->branches.insert(_New_parent->branches.begin(), _Myend);
        }
    }

    _Nodeptr _Myroot; // con tro den root
    _Nodeptr _Myend; // con tro den end
    size_type _Mysize; // so luong phan tu
};

//STRUCT TEMPLATE _Utree_emplace_op2
template<class _Alnode>
struct _Utree_node_emplace_op2 {
    // unbalanced tree emplace operation
    using _Alnode_traits = _STD allocator_traits<_Alnode>;
    using pointer        = typename _Alnode_traits::pointer;
    using size_type      = typename _Alnode_traits::size_type;
    using value_type     = typename _Alnode_traits::value_type;
    using branch_size_t  = typename _STD vector<pointer>::size_type;
  
    template<class... _Valty>
    explicit _Utree_node_emplace_op2(_Alnode& _Al_, pointer _Myroot, _Valty&&... _Val) : _Al(_Al_) {
        _Ptr = value_type::_Buynode(_Al, _Myroot, 1, _STD forward<_Valty>(_Val)...);
    }
    
    ~_Utree_node_emplace_op2() {
        if (_Ptr != pointer{}) {
            value_type::_Freenode(_Al, _Ptr);
        }
    }

    _Utree_node_emplace_op2(const _Utree_node_emplace_op2&) = delete;
    _Utree_node_emplace_op2& operator=(const _Utree_node_emplace_op2&) = delete;

    pointer _Make_branch(pointer _Myend, pointer _Root, branch_size_t _Pos) noexcept {
        // tao 1 nhanh moi cho _Root tai _Pos
        if (_Root == _Myend->parent) {
            return _Transfer_before(_Myend);
        }

        pointer _Result = _Ptr;
        _Ptr            = pointer{};
        _Result->parent = _Root;
        _Result->branches.clear();
        _Root->branches.insert(_Root->branches.begin() + _Pos, _Result);
        return _Result;
    }

    pointer _Transfer_before(pointer _Insert_before) noexcept {
        // chen nut vao truoc _Insert_before 
        pointer _Insert_parent = _Insert_before->parent;
        pointer _Result        = _Ptr;
        _Ptr                   = pointer{};
        _Insert_before->parent = _Result;
        _Result->branches[0]   = _Insert_before;
        _Result->parent        = _Insert_parent;
        _Insert_parent->branches[_Insert_before->branpos] = _Result;
        _STD swap(_Result->branpos, _Insert_before->branpos);
        return _Result;
    }

private:
    pointer _Ptr; 
    _Alnode& _Al;
};

// STRUCT TEMPLATE _Utree_insert_op2
template<class _Alnode>
struct _Utree_node_insert_op2 {
    // unbalanced tree insert operation
    using _Alnode_traits = _STD allocator_traits<_Alnode>;
    using pointer        = typename _Alnode_traits::pointer;
    using size_type      = typename _Alnode_traits::size_type;
    using value_type     = typename _Alnode_traits::value_type;

    explicit _Utree_node_insert_op2(_Alnode& _Al_) : _Al(_Al_), _Added(0), _Head(), _Tail() {}

    _Utree_node_insert_op2(const _Utree_node_insert_op2&) = delete;
    _Utree_node_insert_op2& operator=(const _Utree_node_insert_op2&) = delete;

    template<class... _CArgT>
    void _Append_n(pointer _Myroot, size_type _Count, _CArgT... _Arg) {
        // lien ket _Count phan tu duoc khoi tao tu _Carg
        if (_Count <= 0) {
            return;
        }

        pointer _Newnode;
        if (_Added == 0) {
            _Newnode = value_type::_Buynode(_Al, _Myroot, 1, _STD forward<_CArgT>(_Arg)...);
            _Head    = _Newnode;
            _Tail    = _Newnode;
            _Added++;
            _Count--;
        }

        for (; _Count != 0; --_Count) {
            _Newnode           = value_type::_Buynode(_Al, _Myroot, 1, _STD forward<_CArgT>(_Arg)...);
            _Tail->branches[0] = _Newnode;
            _Newnode->parent   = _Tail;
            _Tail              = _Newnode;
            _Added++;
        }

        _Newnode = pointer{};
    }

    template<class _InIt>
    void _Append_range_unchecked(pointer _Myroot, _InIt _First, _InIt _Last) {
        // lien ket cac gia tri trong [_First, _Last)
        if (_First == _Last) {
            return;
        }

        pointer _Newnode;
        if (_Added == 0) {
            _Newnode = value_type::_Buynode(_Al, _Myroot, 1, *_First);
            _Head    = _Newnode;
            _Tail    = _Newnode;
            _Added++;
            _First++;
        }

        while (_First != _Last) {
            _Newnode           = value_type::_Buynode(_Al, _Myroot, 1, *_First);
            _Tail->branches[0] = _Newnode;
            _Newnode->parent   = _Tail;
            _Tail              = _Newnode;
            _Added++;
            _First++;
        }

        _Newnode = pointer{};
    }

    template<class _Val_types>
    pointer _Attach_before(_Utree_val<_Val_types>& _Utree_data, pointer _Insert_before) {
        // chen cac phan tu da duoc lien ket vao truoc _Insert_before.
        if (_Added == 0) {
            return _Insert_before;
        }

        pointer _Insert_parent = _Insert_before->parent;
        _STD _Construct_in_place(_Head->parent, _Insert_parent);
        _Insert_parent->branches[_Insert_before->branpos] = _Head;
        _STD _Construct_in_place(_Tail->branches[0], _Insert_before);
        _Insert_before->parent = _Tail;
        _STD swap(_Head->branpos, _Insert_before->branpos);
        _Utree_data._Mysize += _Added;
        _Added = 0; 
        return _Head;
    }
    
    ~_Utree_node_insert_op2() {
        if (_Added == 0) {
            return;
        }

        // neu sau khi lien ket ma khong dung, giai phong 
        _STD _Construct_in_place(_Head->parent, pointer{});
        _STD _Construct_in_place(_Tail->branches[0], pointer{});
        pointer _Subject = _Head;
        while (_Subject) {
            value_type::_Freenode(_Al, _STD exchange(_Subject, _Subject->branches[0]));
        }
    }
    
private:
    template<class>
    friend struct _Utree_graft_op;
    _Alnode& _Al;
    size_type _Added; // neu 0, _Head va _Tail khong xac dinh
    pointer _Tail; // tro den phan tu duoc lien ket gan nhat
    pointer _Head; // tro den phan tu duoc lien ket dau tien
};

// STRUCT TEMPLATE _Utree_graft_op
template<class _Alnode>
struct _Utree_graft_op {
    // unbalanced tree graft operation (ghep 1 nhanh moi cho nut)
    using _Alnode_traits = _STD allocator_traits<_Alnode>;
    using pointer        = typename _Alnode_traits::pointer;
    using size_type      = typename _Alnode_traits::size_type;
    using value_type     = typename _Alnode_traits::value_type;
    using branch_size_t  = typename vector<pointer>::size_type;

    explicit _Utree_graft_op(_Alnode& _Al_) : _Al(_Al_), _Length(0), _Head(), _Leaf() {}

    _Utree_graft_op(const _Utree_graft_op&) = delete;
    _Utree_graft_op& operator=(const _Utree_graft_op&) = delete;

    template<class... _CArgT>
    void _Append_n(pointer _Myroot, size_type _Count, _CArgT... _Arg) {
        // lien ket _Count phan tu duoc khoi tao tu _Carg
        if (_Count <= 0) {
            return;
        }

        pointer _Newnode;
        if (_Length == 0) {
            _Newnode = value_type::_Buynode(_Al, _Myroot, 1, _STD forward<_CArgT>(_Arg)...);
            _Head    = _Newnode;
            _Leaf    = _Newnode;
            _Length++;
            _Count--;
        }

        for (; _Count != 0; --_Count) {
            _Newnode           = value_type::_Buynode(_Al, _Myroot, 1, _STD forward<_CArgT>(_Arg)...);
            _Leaf->branches[0] = _Newnode;
            _Newnode->parent   = _Leaf;
            _Leaf              = _Newnode;
            _Length++;
        }

        _Newnode = pointer{};
    }

    template<class _InIt>
    void _Append_range_unchecked(pointer _Myroot, _InIt _First, _InIt _Last) {
        // lien ket cac gia tri trong [_First, _Last)
        if (_First == _Last) {
            return;
        }

        pointer _Newnode;
        if (_Length == 0) {
            _Newnode = value_type::_Buynode(_Al, _Myroot, 1, *_First);
            _Head    = _Newnode;
            _Leaf    = _Newnode;
            _Length++;
            _First++;
        }

        while (_First != _Last) {
            _Newnode           = value_type::_Buynode(_Al, _Myroot, 1, *_First);
            _Leaf->branches[0] = _Newnode;
            _Newnode->parent   = _Leaf;
            _Leaf              = _Newnode;
            _Length++;
            _First++;
        }

        _Newnode = pointer{};
    }

    template<class _Val_types>
    pointer _Graft_branch(_Utree_val<_Val_types>& _Utree_data, pointer _Root, branch_size_t _Branpos) {
        // ghep nhanh vao _Root tai _Branpos
        if (_Length == 0) {
            return _Root;
        }
        
        if (_Root == _Utree_data._Myend->parent) { // neu ghep vao nut cha cua end, chen vao truoc end
            _STL_VERIFY(_Branpos == 0, "graft position for end's parent must be 0");
            _Utree_node_insert_op2<_Alnode> _Op(this->_Al);
            _Op._Head  = this->_Head;
            _Op._Tail  = this->_Leaf;
            _Op._Added = _STD exchange(this->_Length, size_type{0});
            return _Op._Attach_before(_Utree_data, _Utree_data._Myend);
        }

        _Leaf->branches.clear();
        _Root->branches.insert(_Root->branches.begin() + _Branpos, _Head);
        _STD _Construct_in_place(_Head->parent, _Root);
        _Head->branpos       = _Branpos;
        _Utree_data._Mysize += _Length;
        _Length              = 0;
        return _Head;
    }

    ~_Utree_graft_op() {
        if (_Length == 0) {
            return;
        }

        // neu sau khi lien ket ma khong dung, giai phong 
        _STD _Construct_in_place(_Head->parent, pointer{});
        pointer _Subject = _Head;
        while (_Subject != _Leaf) {
            value_type::_Freenode(_Al, _STD exchange(_Subject, _Subject->branches[0]));
        }
        value_type::_Freenode(_Al, _Leaf);
    }
    
private:
    _Alnode& _Al;
    size_type _Length; // do dai cua nhanh. neu 0, _Head va _Leaf khong cac dinh
    pointer _Head; // tro den nut duoc lien ket dau tien
    pointer _Leaf; // tro den nut duoc lien ket cuoi cung
};

[[noreturn]] inline void _Throw_unbalanced_tree_length_error() {
    _Xlength_error("unbalanced tree is too large");
} 

template<class _BranIter, class _Utree_iter>
_INLINE_VAR constexpr bool _Is_bran_iter = _STD _Is_any_of_v<
    _BranIter, _Utree_branch_const_iterator<_Utree_iter>, _Utree_branch_iterator<_Utree_iter>>;

// CLASS TEMPLATE unbalanced_tree
template<class _Ty, class _Alloc = _STD allocator<_Ty>>
class unbalanced_tree { // cay khong can bang
private:
    using _Alty          = _STD _Rebind_alloc_t<_Alloc, _Ty>;
    using _Alty_traits   = _STD allocator_traits<_Alty>;
    using _Node          = _Utree_node<_Ty, typename _STD allocator_traits<_Alloc>::void_pointer>;
    using _Alnode        = _STD _Rebind_alloc_t<_Alloc, _Node>;
    using _Alnode_traits = _STD allocator_traits<_Alnode>;
    using _Nodeptr       = typename _Alnode_traits::pointer;

    using _Val_types = _STD conditional_t<_STD _Is_simple_alloc_v<_Alnode>, _Utree_simple_types<_Ty>,
        _Utree_iter_types<_Ty, typename _Alty_traits::size_type, typename _Alty_traits::difference_type,
        typename _Alty_traits::pointer, typename _Alty_traits::const_pointer, _Ty&, const _Ty&, _Nodeptr>>;

    using _Scary_val = _Utree_val<_Val_types>;

public:
    static_assert(!_ENFORCE_MATCHING_ALLOCATORS || is_same_v<_Ty, typename _Alloc::value_type>,
        _MISMATCHED_ALLOCATOR_MESSAGE("unbalanced_tree<T, Allocator>", "T"));

    using value_type      = _Ty;
    using allocator_type  = _Alloc;
    using size_type       = typename _Alty_traits::size_type;
    using branch_size_t   = typename _STD vector<_Nodeptr>::size_type;
    using difference_type = typename _Alty_traits::difference_type;
    using pointer         = typename _Alty_traits::pointer;
    using const_pointer   = typename _Alty_traits::const_pointer;
    using reference       = value_type&;
    using const_reference = const value_type&;

    using iterator                  = _Utree_iterator<_Scary_val>;
    using const_iterator            = _Utree_const_iterator<_Scary_val>;
    using _Unchecked_iterator       = _Utree_unchecked_iterator<_Scary_val>;
    using _Unchecked_const_iterator = _Utree_unchecked_const_iterator<_Scary_val>;

    using reverse_iterator       = _STD reverse_iterator<iterator>;
    using const_reverse_iterator = _STD reverse_iterator<const_iterator>;

    struct copy_tag{};
    struct move_tag{};

    unbalanced_tree() : _Mypair(_STD _Zero_then_variadic_args_t()) {
        _Alloc_sentinel_and_proxy();
    }

    explicit unbalanced_tree(const _Alloc& _Al) : _Mypair(_STD _One_then_variadic_args_t(), _Al) {
        _Alloc_sentinel_and_proxy();
    }

private:
    void _Copy_construct(const unbalanced_tree& _Right) {
        auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alnode, _Getal());
        _STD _Container_proxy_ptr<_Alnode> _Proxy(_Alproxy, *_Get_scary());
        auto& _Right_data     = *_Right._Get_scary();
        _Get_scary()->_Myroot = _Node::_Buyroot(_Getal(), _Right_data._Myroot->branches.size());
        _Get_scary()->_Myend  = _Node::_Buyend(_Getal());
        _Copy(_Right, copy_tag());
        _Proxy._Release();
    }

    template<class _Moveit>
    void _Copy(const unbalanced_tree& _Right, _Moveit _Movefl) {
        auto& _My_data    = *_Get_scary();
        auto& _Right_data = *_Right._Get_scary();
        _My_data._Mysize  = _Right_data._Mysize;
        if (_My_data._Mysize == 0) { // cay trong, lien ket root voi end
            _Get_scary()->_Myroot->branches[0] = _Get_scary()->_Myend;
            _Get_scary()->_Myend->parent       = _Get_scary()->_Myroot;
        } else {
            _Get_scary()->_Myend->parent = NULL;
            _Nodeptr _End_parent         = _Right_data._Myend->parent;
            _End_parent->branches[0]     = NULL;
            _End_parent->branches.clear();
            _Copy_branches(_Right_data._Myroot, _My_data._Myroot, _Movefl);
            _My_data._To_new_end();
            _End_parent->branches.insert(_End_parent->branches.begin(), _Right_data._Myend);
        }
    }

    template<class _Moveit>
    void _Copy_branches(_Nodeptr _Rootnode, _Nodeptr _Wherenode, _Moveit _Movefl) {
        // copy tat ca nhanh cua _Rootnode
        for (branch_size_t _Branidx = 0; _Branidx < _Wherenode->branches.size(); ++_Branidx) {
            _Nodeptr _Pnode                = _Copy_node(_Rootnode->branches[_Branidx], _Wherenode, _Movefl);
            _Wherenode->branches[_Branidx] = _Pnode;
            if (_Pnode->branches.size() != 0) {
                _TRY_BEGIN
                _Copy_branches(_Rootnode->branches[_Branidx], _Pnode, _Movefl);
                _CATCH_ALL
                // copy that bai, xoa
                iterator _Erase(_Pnode, _Get_scary());
                while (_Erase._Ptr != _Get_scary()->_Myroot) {
                    _Node::_Freenode(_Getal(), (_Erase--)._Ptr);
                }
                _Erase._Orphan_me();
                _RERAISE;
                _CATCH_END
            }
        }
    }

    template<class _Ty>
    _Nodeptr _Copy_or_move(_CRT_GUARDOVERFLOW branch_size_t _Bransize, _Ty& _Val, copy_tag) { // copy (gia tri) den nut moi
        return _Buynode(_Bransize, _Val);
    }

    template<class _Ty>
    _Nodeptr _Copy_or_move(_CRT_GUARDOVERFLOW branch_size_t _Bransize, _Ty& _Val, move_tag) { // move (gia tri) den nut moi
        return _Buynode(_Bransize, _STD move(_Val));
    }

    template<class _Moveit>
    _Nodeptr _Copy_node(_Nodeptr _Brannode, _Nodeptr _Parent, _Moveit _Movefl) {
        _Nodeptr _Pnode = _Copy_or_move(_Brannode->branches.size(), _Brannode->_Myval, _Movefl);
        _Pnode->branpos = _Brannode->branpos;
        _Pnode->parent  = _Parent;
        return _Pnode;
    }

public:
    unbalanced_tree(const unbalanced_tree& _Right)
        : _Mypair(_STD _One_then_variadic_args_t(), _Alnode_traits::select_on_container_copy_construction(_Right._Getal())) {
        _Copy_construct(_Right);
    }

    unbalanced_tree(const unbalanced_tree& _Right, const _Alloc& _Al) : _Mypair(_STD _One_then_variadic_args_t(), _Al) {
        _Copy_construct(_Right);
    }

private:
    void _Different_allocator_move_construct(unbalanced_tree&& _Right) {
        auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alnode, _Getal());
        _STD _Container_proxy_ptr<_Alnode> _Proxy(_Alproxy, *_Get_scary());
        auto& _Right_data     = *_Right._Get_scary();
        _Get_scary()->_Myroot = _Node::_Buyroot(_Getal(), _Right_data._Myroot->branches.size());
        _Get_scary()->_Myend  = _Node::_Buyend(_Getal());
        _Copy(_Right, move_tag());
        _Proxy._Release();
    }

public:
    unbalanced_tree(unbalanced_tree&& _Right) noexcept : _Mypair(_STD _One_then_variadic_args_t(), _STD move(_Right._Getal())) {
        _Alloc_sentinel_and_proxy();
        _Swap_val(_Right);
    }

    unbalanced_tree(unbalanced_tree&& _Right, const allocator_type& _Al) : _Mypair(_STD _One_then_variadic_args_t(), _Al) {
        if
            _CONSTEXPR_IF(!_Alnode_traits::is_always_equal::value) {
            if (_Getal() != _Right._Getal()) {
                _Different_allocator_move_construct(_STD move(_Right));
                return;
            }
        }

        _Alloc_sentinel_and_proxy();
        _Swap_val(_Right);
    }

private:
    void _Move_assign(unbalanced_tree& _Right, _STD _Equal_allocators) noexcept {
        clear();
        _STD _Pocma(_Getal(), _Right._Getal());
        _Swap_val(_Right);
    }

    void _Move_assign(unbalanced_tree& _Right, _STD _Propagate_allocators) {
        if (_Getal() == _Right._Getal()) {
            _Move_assign(_Right, _STD _Equal_allocators{});
        } else {
            auto&& _Alproxy       = _GET_PROXY_ALLOCATOR(_Alnode, _Getal());
            auto&& _Right_alproxy = _GET_PROXY_ALLOCATOR(_Alnode, _Right._Getal());
            _STD _Container_proxy_ptr<_Alty> _Proxy(_Right_alproxy, _STD _Leave_proxy_unbound{});
            auto& _My_data      = *_Get_scary();
            auto& _Right_data   = *_Right._Get_scary();
            const auto _Newroot = _STD exchange(_Right_data._Myroot, _Node::_Buyroot(_Right._Getal()));
            const auto _Newend  = _STD exchange(_Right_data._Myend, _Node::_Buyend(_Right._Getal()));
            const auto _Newsize = _STD exchange(_Right_data._Mysize, size_type{0});
            _Tidy();
            _STD _Pocma(_Getal(), _Right._Getal());
            _My_data._Myroot                 = _Newroot;
            _My_data._Myend                  = _Newend;
            _My_data._Mysize                 = _Newsize;
            _Right_data._Myroot->branches[0] = _Right_data._Myend;
            _Right_data._Myend->parent       = _Right_data._Myroot;
            _Proxy._Bind(_Alproxy, _Get_scary());
            _My_data._Swap_proxy_and_iterators(_Right_data);
        }
    }

    void _Move_assign(unbalanced_tree& _Right, _STD _No_propagate_allocators) {
        if (_Getal() == _Right._Getal()) {
            _Move_assign(_Right, _STD _Equal_allocators{});
        } else {
            clear();
            _Copy(_Right, move_tag());
        }
    }

public:
    unbalanced_tree& operator=(unbalanced_tree&& _Right) noexcept(
        noexcept(_Move_assign(_Right, _STD _Choose_pocma<_Alnode>{}))) {
        if (this != _STD addressof(_Right)) {
            _Move_assign(_Right, _STD _Choose_pocma<_Alnode>{});
        }

        return *this;
    }

private:
    void _Copy_assign(const unbalanced_tree& _Right, false_type) {
        auto& _My_data    = *_Get_scary();
        auto& _Right_data = *_Right._Get_scary();
        clear();
        _STD _Pocca(_Getal(), _Right._Getal());
        _My_data._Myroot->branches.resize(
            _Right_data._Myroot->branches.size());
        _Copy(_Right, copy_tag());
    }

    void _Copy_assign(const unbalanced_tree& _Right, true_type) {
        if (_Getal() == _Right._Getal()) {
            _Copy_assign(_Right, false_type{});
        } else {
            auto& _Al             = _Getal();
            auto&& _Alproxy       = _GET_PROXY_ALLOCATOR(_Alnode, _Al);
            auto& _Right_al       = _Right._Getal();
            auto&& _Right_alproxy = _GET_PROXY_ALLOCATOR(_Alnode, _Right_al);
            _STD _Container_proxy_ptr<_Alty> _Proxy(_Right_alproxy, _STD _Leave_proxy_unbound{});
            auto _Right_al_non_const = _Right_al;
            auto _Newroot            = _Node::_Buyroot(_Right_al_non_const, _Right._Get_scary()->_Myroot.branches.size());
            auto _Newend             = _Node::_Buyend(_Right_al_non_const);
            _Tidy();
            _STD _Pocca(_Al, _Right_al);
            _Get_scary()->_Myroot = _Newroot;
            _Get_scary()->_Myend  = _Newend;
            _Proxy._Bind(_Alproxy, _Get_scary());
            _Copy(_Right, copy_tag());
        }
    }

public:
    unbalanced_tree& operator=(const unbalanced_tree& _Right) {
        if (this != _STD addressof(_Right)) {
            _Copy_assign(_Right, _STD _Choose_pocca<_Alnode>{});
        }

        return *this;
    }

    ~unbalanced_tree() noexcept {
        _Tidy();
#if _ITERATOR_DEBUG_LEVEL != 0 
        auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alnode, _Getal());
        _STD _Delete_plain_internal(_Alproxy, _Mypair._Myval2._Myproxy);
#endif // _ITERATOR_DEBUG_LEVEL != 0
    }

private:
    void _Swap_val(unbalanced_tree& _Right) noexcept { // swap voi _Right, allocator giong nhau
        auto& _My_data    = *_Get_scary();
        auto& _Right_data = *_Right._Get_scary();
        _My_data._Swap_proxy_and_iterators(_Right_data);
        _STD _Swap_adl(_My_data._Myroot, _Right_data._Myroot);
        _STD _Swap_adl(_My_data._Myend, _Right_data._Myend);
        _STD swap(_My_data._Mysize, _Right_data._Mysize);
    }

public:
    void transfer(const_iterator _From, branch_size_t _From_pos, const_iterator _To, branch_size_t _To_pos) {
        // chuyen nhanh tai _From_pos tai _From cho _To tai _To_pos
        if (_From.bran_size() == 0 || _From._Ptr == _Get_scary()->_Myend->parent) {
            return;
        }

#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_From._Getcont() == _Get_scary(), "branch to transfer is outside range");
        _STL_VERIFY(_From_pos < _From.bran_size() && _To_pos <= _To.bran_size(), "branch subcript out of range ");
#endif // _ITERATOR_DEBUG_LEVEL == 2
        
        auto _First = _From.bran_begin() + _From_pos;
        auto _Last  = _STD _Next_iter(_First);
        auto _Dest  = _To.bran_begin() + _To_pos;

        if (_From._Getcont() == _To._Getcont()) {
            if (_To._Ptr == _Get_scary()->_Myend->parent) {
                _STL_VERIFY(_To_pos == 0, "position to transfer branch to end's parent must be 0");
            }
            _Local_transfer(_First, _Last, _Dest);
        } else {
            auto _Other_cont = static_cast<_Scary_val*>(const_cast<_STD _Container_base12*>(_To._Getcont()));
            if (_To._Ptr == _Other_cont->_Myend->parent) {
                _STL_VERIFY(_To_pos == 0, "position to transfer branch to end's parent must be 0");
            }
            _Transfer_to_other_tree(_First, _Last, _Dest, *_Other_cont);
        }
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    void transfer(_BranIter _Branch, _BranIter _Dest) { // chuyen _Branch den [..., _Dest)
        auto _From = _Branch.get_root();
        auto _To   = _Dest.get_root();
        if (_From.bran_size() == 0 || _From._Ptr == _Get_scary()->_Myend->parent) {
            return;
        }

#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_From._Getcont() == _Get_scary(), "branch to transfer is outside range");     
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_From._Getcont() == _To._Getcont()) {
            if (_To._Ptr == _Get_scary()->_Myend->parent) {
#if _ITERATOR_DEBUG_LEVEL == 2
                _STL_VERIFY(_Dest._Unwrapped() == _To.bran_begin()._Unwrapped(),
                    "branch iterator to transfer branch to end's parent must be the first branch");
#endif // _ITERATOR_DEBUG_LEVEL == 2 
            }
            _Local_transfer(_Branch, _Branch + 1, _Dest);
        } else {
            auto _Other_cont = static_cast<_Scary_val*>(const_cast<_STD _Container_base12*>(_To._Getcont()));
            if (_To._Ptr == _Other_cont->_Myend->parent) {
#if _ITERATOR_DEBUG_LEVEL == 2
                _STL_VERIFY(_Dest._Unwrapped() == _To.bran_begin()._Unwrapped(),
                    "branch iterator to transfer branch to end's parent must be the first branch");
#endif // _ITERATOR_DEBUG_LEVEL == 2 
            }
            _Transfer_to_other_tree(_Branch, _Branch + 1, _Dest, *_Other_cont);
        }
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    void transfer(_BranIter _First, _BranIter _Last, _BranIter _Dest) { // chuyen cac nhanh trong [_First, _Last) den _Dest
        auto _From = _First.get_root();
        auto _To   = _Dest.get_root();
        if (_From.bran_size() == 0 || _From._Ptr == _Get_scary()->_Myend->parent) {
            return;
        }

#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_From._Getcont() == _Get_scary(), "branch to transfer is outside range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_From._Getcont() == _To._Getcont()) {
            if (_To._Ptr == _Get_scary()->_Myend->parent) {
#if _ITERATOR_DEBUG_LEVEL == 2
                _STL_VERIFY(_Dest._Unwrapped() == _To.bran_begin()._Unwrapped(),
                    "branch iterator to transfer branch to end's parent must be the first branch");
#endif // _ITERATOR_DEBUG_LEVEL == 2 
            }
            _Local_transfer(_First, _Last, _Dest);
        } else {
            auto _Other_cont = static_cast<_Scary_val*>(const_cast<_STD _Container_base12*>(_To._Getcont()));
            if (_To._Ptr == _Other_cont->_Myend->parent) {
#if _ITERATOR_DEBUG_LEVEL == 2
                _STL_VERIFY(_Dest._Unwrapped() == _To.bran_begin()._Unwrapped(),
                    "branch iterator to transfer branch to end's parent must be the first branch");
#endif // _ITERATOR_DEBUG_LEVEL == 2 
            }
            _Transfer_to_other_tree(_First, _Last, _Dest, *_Other_cont);
        }
    }

private:
    template<class _BranIter>
    void _Local_transfer(_BranIter _First, _BranIter _Last, _BranIter _Dest) {
        _STD _Adl_verify_range(_First, _Last);
        _Nodeptr _From = _First.get_root()._Ptr;
        _Nodeptr _To   = _Dest.get_root()._Ptr;
        auto _UFirst   = _First._Unwrapped();
        auto _ULast    = _Last._Unwrapped();
        auto _UDest    = _Dest._Unwrapped();

        if (_From == _To) {
            if (_From->branches.size() == 1) {
                return;
            }
            if (_UFirst <= _UDest && _UDest <= _ULast) {
                return;
            } else if (_UDest < _UFirst) {  // chuyen cac nhanh trong [_First, _Last) den [_Dest, ...)
                _STL_VERIFY(_UDest >= _STD _Get_unwrapped(_From->branches.begin()), "_Dest outside range");
                _STD vector<_Nodeptr> _Branptr;
                auto _UNext = _UDest;
                while (_UNext != _UFirst) {
                    _Branptr.push_back(*_UNext);
                    *_UNext = NULL;
                    ++_UNext;
                }
                while (_UNext != _ULast) {
                    *_UDest = *_UNext;
                    ++_UDest;
                    ++_UNext;
                }
                _UNext = _UDest;
                auto _BFirst = _STD _Get_unwrapped(_Branptr.begin());
                auto _BLast  = _STD _Get_unwrapped(_Branptr.end());
                while (_BFirst != _BLast) {
                    *_UNext = *_BFirst;
                    *_BFirst = NULL;
                    ++_BFirst;
                    ++_UNext;
                }
                _Get_scary()->_Branch_change_pos(_From);
                _Get_scary()->_To_new_end();
            } else { // chuyen cac nhanh trong [_First, _Last) den [..., _Dest)
                _STL_VERIFY(_UDest <= _STD _Get_unwrapped(_From->branches.end()), "_Dest outside range");
                _STD vector<_Nodeptr> _Branptr;
                auto _UPrev = _UDest;
                while (_UPrev != _ULast) {
                    _Branptr.push_back(*--_UPrev);
                    *_UPrev = NULL;
                }
                while (_UPrev != _UFirst) {
                    *--_UDest = *--_UPrev;
                }
                auto _BFirst = _STD _Get_unwrapped(_Branptr.begin());
                auto _BLast  = _STD _Get_unwrapped(_Branptr.end());
                while (_UDest != _UFirst) {
                    *--_UDest = *_BFirst;
                    ++_BFirst;
                }
                _Get_scary()->_Branch_change_pos(_From);
                _Get_scary()->_To_new_end();
            }
        } else { // chuyen cac nhanh trong [_First, _Last) den _Dest cua mot nut khac
            _STL_VERIFY(_To != _Get_scary()->_Myend, "cannot transfer branch to end");
            branch_size_t _Upper = _UFirst - _STD _Get_unwrapped(_From->branches.begin());
            branch_size_t _Lower = _ULast - _STD _Get_unwrapped(_From->branches.begin());
            _STL_VERIFY(!_In_bran(_From, _To, _Upper, _Lower), "where to receive branches is in transferred branches");
            if (_To == _Get_scary()->_Myend->parent) {
                _To->branches[0] = NULL;
                _To->branches.clear();
                _Get_scary()->_Myend->parent = NULL;
            }

            branch_size_t _Inserted_pos  = _UDest - _STD _Get_unwrapped(_To->branches.begin());
            branch_size_t _Transfer_size = static_cast<branch_size_t>(_ULast - _UFirst);
            _To->branches.insert(_To->branches.begin() + _Inserted_pos, _Transfer_size, nullptr);
            auto _Transferred = _STD _Get_unwrapped(_To->branches.begin()) + _Inserted_pos;

            while (_UFirst != _ULast) {
                *_Transferred      = *_UFirst;
                (*_UFirst)->parent = _To;
                *_UFirst           = NULL;
                ++_UFirst;
                ++_Transferred;
            }

            _From->branches.erase(_First.get_branch(), _Last.get_branch());
            _Get_scary()->_Branch_change_pos(_From);
            _Get_scary()->_Branch_change_pos(_To);
            _Get_scary()->_To_new_end();
        }
    }

    template<class _BranIter>
    void _Transfer_to_other_tree(_BranIter _First, _BranIter _Last, _BranIter _Dest, _Scary_val& _Other) {
        // chuyen cac nhanh trong [_First, _Last) den _Dest cua mot cay khac
        _STD _Adl_verify_range(_First, _Last);
        _Nodeptr _From = _First.get_root()._Ptr;
        _Nodeptr _To   = _Dest.get_root()._Ptr;
        auto _UFirst   = _First._Unwrapped();
        auto _ULast    = _Last._Unwrapped();
        auto _UDest    = _Dest._Unwrapped();

        _STL_VERIFY(_To != _Other._Myend, "cannot transfer branch to end");

        _Nodeptr _Firsthead = *_First;
        _Nodeptr _Lastleaf  = *(_ULast - 1);
        while (_Lastleaf->branches.size() != 0) {
            _Lastleaf = _Lastleaf->branches.back();
        }
        
        bool _End_in_move = _Lastleaf == _Get_scary()->_Myend; 
        // neu nut end trong cac nhanh se chuyen, tam thoi ngat lien ket
        if (_End_in_move) { 
            _Lastleaf              = _Lastleaf->parent;
            _Lastleaf->branches[0] = NULL;
            _Lastleaf->branches.clear();
            _Get_scary()->_Myend->parent = NULL;
        }

        if (_To == _Other._Myend->parent) {
            _To->branches[0] = NULL;
            _To->branches.clear();
            _Other._Myend->parent = NULL;
        }
        
        // chuyen cac iterator
        size_type _Child_size = 1; // kich thuoc cua (cac) nhanh
        iterator _Next(_Lastleaf, _Get_scary());
        _Nodeptr _Marked;
        while (_Next._Ptr != _Firsthead) { 
            _Marked = (_Next--)._Ptr; 
#if _ITERATOR_DEBUG_LEVEL == 2
            _Other._Adopt_ptr(*_Get_scary(), _Marked);
#endif // _ITERATOR_DEBUG_LEVEL == 2

            ++_Child_size;
        }
        _Next._Orphan_me();
        _Other._Adopt_ptr(*_Get_scary(), _Firsthead);

        branch_size_t _Inserted_pos  = _UDest - _STD _Get_unwrapped(_To->branches.begin());
        branch_size_t _Transfer_size = static_cast<branch_size_t>(_ULast - _UFirst);
        _To->branches.insert(_To->branches.begin() + _Inserted_pos, _Transfer_size, nullptr);
        auto _Transferred = _STD _Get_unwrapped(_To->branches.begin()) + _Inserted_pos;

        while (_UFirst != _ULast) {
            *_Transferred      = *_UFirst;
            (*_UFirst)->parent = _To;
            *_UFirst           = NULL;
            ++_UFirst;
            ++_Transferred;
        }

        _From->branches.erase(_First.get_branch(), _Last.get_branch());
        _Get_scary()->_Branch_change_pos(_From);
        _Get_scary()->_Branch_change_pos(_To);
        _Get_scary()->_To_new_end();
        _Other._To_new_end();
        _Get_scary()->_Mysize -= _Child_size;
        _Other._Mysize        += _Child_size;
    }

public:
    void clear() noexcept {
        _Get_scary()->_Orphan_except_root_end();
        auto _Erased  = _STD _Prev_iter(end());
        auto& _Mydata = *_Get_scary();
        while (_Erased._Ptr != _Mydata._Myroot) {
            _Node::_Freenode(_Getal(), (_Erased--)._Ptr);
        }
        _Erased._Orphan_me();
        _Mydata._Myroot->branches.clear();
        _Mydata._Myroot->branches.insert(_Mydata._Myroot->branches.begin(), _Mydata._Myend);
        _Mydata._Myend->parent = _Mydata._Myroot;
        _Mydata._Mysize        = 0;
    }

public: 
    iterator insert(const_iterator _Where, value_type&& _Val) { // chen _Val tai _Where
        return emplace(_Where, _STD move(_Val));
    }

    iterator insert(const_iterator _Where, const value_type& _Val) { // chen _Val tai _Where
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Where._Getcont() == _Get_scary(), "unbalanced tree insert iterator is outside range");
        _STL_VERIFY(_Where._Ptr != _Get_scary()->_Myroot, "cannot insert before root");
#endif // _ITERATOR_DEBUG_LEVEL == 2


        return _Make_iter(_Emplace(_Where._Ptr, _Val));
    }

    iterator insert(const_iterator _Where, _CRT_GUARDOVERFLOW size_type _Count, const value_type& _Val) {
        // chen _Count * _Val truoc _Where
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Where._Getcont() == _Get_scary(), "unbalanced tree insert iterator is outside range");
        _STL_VERIFY(_Where._Ptr != _Get_scary()->_Myroot, "cannot insert before root");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        _Utree_node_insert_op2<_Alnode> _Op(_Getal());
        _Op._Append_n(_Get_scary()->_Myroot, _Count, _Val);
        return _Make_iter(_Op._Attach_before(*_Get_scary(), _Where._Ptr));
    }

    iterator insert(const_iterator _Where, _STD initializer_list<value_type> _Ilist) {
        // chen danh sach khoi tao tai _Where
        return insert(_Where, _Ilist.begin(), _Ilist.end());
    }

    template<class _Iter, _STD enable_if_t<_STD _Is_iterator_v<_Iter> && _STD is_same_v<_STD _Iter_value_t<_Iter>, value_type>, int> = 0>
    iterator insert(const_iterator _Where, _Iter _First, _Iter _Last) {
        // chen [_First, _Last) tai _Where
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Where._Getcont() == _Get_scary(), "unbalanced tree insert iterator is outside range");
        _STL_VERIFY(_Where._Ptr != _Get_scary()->_Myroot, "cannot insert before root");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        _STD _Adl_verify_range(_First, _Last);
        _Utree_node_insert_op2<_Alnode> _Op(_Getal());
        _Op._Append_range_unchecked(_Get_scary()->_Myroot, _First, _Last);
        return _Make_iter(_Op._Attach_before(*_Get_scary(), _Where._Ptr));
    }

    template<class... _Valty>
    iterator emplace(const_iterator _Where, _Valty&&... _Val) { // chen _Val tai _Where
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Where._Getcont() == _Get_scary(), "unbalanced tree emplace iterator is outside range");
        _STL_VERIFY(_Where._Ptr != _Get_scary()->_Myroot, "cannot insert before root");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return _Make_iter(_Emplace(_Where._Ptr, _STD forward<_Valty>(_Val)...));
    }

    template<class... _Valty>
    _Nodeptr _Emplace(const _Nodeptr _Where, _Valty&&... _Val) {
        size_type& _Mysize = _Get_scary()->_Mysize;
        if (_Mysize == max_size()) {
            _Xlength_error("unbalanced tree is too large");
        }

        _Utree_node_emplace_op2<_Alnode> _Op(_Getal(), _Get_scary()->_Myroot, _STD forward<_Valty>(_Val)...);
        ++_Mysize;
        return _Op._Transfer_before(_Where);
    }

public: 
    iterator graft(const_iterator _Root, branch_size_t _Branpos, value_type&& _Val) { // tao mot nhanh moi cho _Root tai _Branpos
        return emplace_graft(_Root, _Branpos, _STD move(_Val));
    }

    iterator graft(const_iterator _Root, branch_size_t _Branpos, const value_type& _Val) { // tao mot nhanh moi cho _Root tai _Branpos
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "unbalanced tree graft iterator outside range");
        _STL_VERIFY(_Root._Ptr != _Get_scary()->_Myend, "cannot graft branch to end");
        _STL_VERIFY(_Branpos <= _Root._Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_Root._Ptr == _Get_scary()->_Myend->parent) {
            _STL_VERIFY(_Branpos == 0, "graft position for end's parent must be 0");
        }
        return _Make_iter(_Emplace_graft(_Root._Ptr, _Branpos, _Val));
    }

    iterator graft(
        const_iterator _Root, branch_size_t _Branpos, _CRT_GUARDOVERFLOW size_type _Count, const value_type& _Val) {
        // tao mot nhanh (_Count * _Val) cho _Root tai _Branpos
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "unbalanced tree graft iterator outside range");
        _STL_VERIFY(_Root._Ptr != _Get_scary()->_Myend, "cannot graft branch to end");
        _STL_VERIFY(_Branpos <= _Root._Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_Root._Ptr == _Get_scary()->_Myend->parent) {
            _STL_VERIFY(_Branpos == 0, "graft position for end's parent must be 0");
        }
        _Utree_graft_op<_Alnode> _Op(_Getal());
        _Op._Append_n(_Get_scary()->_Myroot, _Count, _Val);
        _Nodeptr _Result = _Op._Graft_branch(*_Get_scary(), _Root._Ptr, _Branpos);

        if (_Root != _Get_scary()->_Myend->parent) {
            _Get_scary()->_Branch_change_pos(_Root);
            _Get_scary()->_To_new_end();
        }

        return _Make_iter(_Result);
    }

    template<class _Iter, _STD  enable_if_t<_STD _Is_iterator_v<_Iter> && _STD is_same_v<_STD _Iter_value_t<_Iter>, value_type>, int> = 0>
    iterator graft(const_iterator _Root, branch_size_t _Branpos, _Iter _First, _Iter _Last) {
        // tao mot nhanh (tu [_First, _Last)) cho _Root tai _Branpos
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "unbalanced tree graft iterator outside range");
        _STL_VERIFY(_Root._Ptr != _Get_scary()->_Myend, "cannot graft branch to end");
        _STL_VERIFY(_Branpos <= _Root._Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_Root._Ptr == _Get_scary()->_Myend->parent) {
            _STL_VERIFY(_Branpos == 0, "graft position for end's parent must be 0");
        }
        _STD _Adl_verify_range(_First, _Last);
        _Utree_graft_op<_Alnode> _Op(_Getal());
        _Op._Append_range_unchecked(_Get_scary()->_Myroot, _First, _Last);
        _Nodeptr _Result = _Op._Graft_branch(*_Get_scary(), _Root._Ptr, _Branpos);

        if (_Root._Ptr != _Get_scary()->_Myend->parent) {
            _Get_scary()->_Branch_change_pos(_Root._Ptr);
            _Get_scary()->_To_new_end();
        }

        return _Make_iter(_Result);
    }

    iterator graft(const_iterator _Root, branch_size_t _Branpos, _STD initializer_list<value_type> _Ilist) {
        // tao mot nhanh moi tu danh sach khoi tao cho _Root tai _Branbos
        return graft(_Root, _Branpos, _Ilist.begin(), _Ilist.end());
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    iterator graft(_BranIter _Branch, value_type&& _Val) { // tao mot nhanh moi = branch_iterator
        return emplace_graft(_Branch, _STD move(_Val));
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    iterator graft(_BranIter _Branch, const value_type& _Val) { // tao mot nhanh moi = branch_iterator
        auto _Myroot           = static_cast<const_iterator>(_Branch.get_root());
        branch_size_t _Branpos = static_cast<branch_size_t>(
            _Branch.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));
        return graft(_Myroot, _Branpos, _Val);
    }

    template<class _BranIter, enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    iterator graft(_BranIter _Branch, _CRT_GUARDOVERFLOW size_type _Count, const value_type& _Val) { // tao mot nhanh (_Count * _Val) moi = branch_iterator
        auto _Myroot           = static_cast<const_iterator>(_Branch.get_root());
        branch_size_t _Branpos = static_cast<branch_size_t>(
            _Branch.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));
        return graft(_Myroot, _Branpos, _Count, _Val);
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0,
        class _Iter, _STD  enable_if_t<_STD _Is_iterator_v<_Iter> && _STD is_same_v<_STD _Iter_value_t<_Iter>, value_type>, int> = 0>
    iterator graft(_BranIter _Branch, _Iter _First, _Iter _Last) { // tao mot nhanh [_First, _Last) moi = branch_iterator
        auto _Myroot           = static_cast<const_iterator>(_Branch.get_root());
        branch_size_t _Branpos = static_cast<branch_size_t>(
            _Branch.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));
        return graft(_Myroot, _Branpos, _First, _Last);
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    iterator graft(_BranIter _Branch, _STD initializer_list<value_type> _Ilist) { // tao mot nhanh moi tu danh sach khoi tao = branch_iterator
        auto _Myroot           = static_cast<const_iterator>(_Branch.get_root());
        branch_size_t _Branpos = static_cast<branch_size_t>(
            _Branch.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));
        return graft(_Myroot, _Branpos, _Ilist.begin(), _Ilist.end());
    }

    template<class... _Valty>
    iterator emplace_graft(const_iterator _Root, branch_size_t _Branpos, _Valty&&... _Val) { // tao mot nhanh moi cho _Root tai _Branpos
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "unbalanced tree emplace iterator outside range");
        _STL_VERIFY(_Root._Ptr != _Get_scary()->_Myend, "cannot graft branch to end");
        _STL_VERIFY(_Branpos <= _Root._Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_Root._Ptr == _Get_scary()->_Myend->parent) {
            _STL_VERIFY(_Branpos == 0, "graft position for end's parent must be 0");
        }
        return _Make_iter(_Emplace_graft(_Root._Ptr, _Branpos, _STD forward<_Valty>(_Val)...));
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0, class... _Valty>
    iterator emplace_graft(_BranIter _Branch, _Valty&&... _Val) { // tao mot nhanh moi = branch_iterator
        auto _Myroot           = static_cast<const_iterator>(_Branch.get_root());
        branch_size_t _Branpos = static_cast<branch_size_t>(
            _Branch.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));
        return emplace_graft(_Myroot, _Branpos, _STD forward<_Valty>(_Val)...);
    }

    template<class... _Valty>
    _Nodeptr _Emplace_graft(const _Nodeptr _Root, branch_size_t _Branpos, _Valty&&... _Val) { // tao mot nhanh moi cho _Root tai _Branpos
        size_type& _Mysize = _Get_scary()->_Mysize; 
        if (_Mysize == max_size()) {
            _STD _Xlength_error("unbalanced tree is too large");
        }

        _Utree_node_emplace_op2<_Alnode> _Op(_Getal(), _Get_scary()->_Myroot, _STD forward<_Valty>(_Val)...);
        ++_Mysize;
        auto _Result = _Op._Make_branch(_Get_scary()->_Myend, _Root, _Branpos);

        if (_Root != _Get_scary()->_Myend->parent) {
            _Get_scary()->_Branch_change_pos(_Root);
            _Get_scary()->_To_new_end();
        }
        return _Result;
    }

    iterator multiple_graft( // ghep nhieu danh sach khoi tao vao _Root tai _Branpos
        const_iterator _Root, branch_size_t _Branpos, _STD initializer_list<_STD initializer_list<value_type>> _Branlist) {
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "unbalanced tree multiple graft iterator outside range");
        _STL_VERIFY(_Root._Ptr != _Get_scary()->_Myend, "cannot graft branch to end");
        _STL_VERIFY(_Branpos <= _Root._Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_Root._Ptr == _Get_scary()->_Myend->parent) {
            _STL_VERIFY(_Branpos == 0, "graft position for end's parent must be 0");
        }
        auto _First   = _Branlist.begin();
        auto _Nextpos = _Branpos;
        _Utree_graft_op<_Alnode> _Op(_Getal());

        while (_First != _Branlist.end()) {
            _Op._Append_range_unchecked(_Get_scary()->_Myroot, (*_First).begin(), (*_First).end());
            _Op._Graft_branch(*_Get_scary(), _Root._Ptr, _Nextpos);
            _First++;
            _Nextpos++;
        }
        _Get_scary()->_Branch_change_pos(_Root._Ptr);
        _Get_scary()->_To_new_end();
        return _Make_iter(_Root._Ptr->branches[_Branpos]);
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    iterator multiple_graft(_BranIter _Branch, _STD initializer_list<_STD initializer_list<value_type>> _Branlist)  { // ghep nhieu danh sach khoi tao = branch_iterator
        auto _Myroot           = static_cast<const_iterator>(_Branch.get_root());
        branch_size_t _Branpos = static_cast<branch_size_t>(
            _Branch.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));
        return multiple_graft(_Myroot, _Branpos, _Branlist);
    }

    template<class _Iter, _STD enable_if_t<_STD _Is_iterator_v<_Iter> && _STD is_same_v<_STD _Iter_value_t<_Iter>, value_type>, int> = 0>
    iterator multiple_graft(const_iterator _Root, branch_size_t _Branpos, _STD initializer_list<_STD pair<_Iter, _Iter>> _Iterlist) {
        // ghep nhieu nhanh vao _Root tai _Branpos
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "unbalanced tree multiple graft iterator outside range");
        _STL_VERIFY(_Root._Ptr != _Get_scary()->_Myend, "cannot graft branch to end");
        _STL_VERIFY(_Branpos <= _Root._Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_Root._Ptr == _Get_scary()->_Myend->parent) {
            _STL_VERIFY(_Branpos == 0, "graft position for end's parent must be 0");
        }
        auto _First   = _Iterlist.begin();
        auto _Last    = _Iterlist.end();
        auto _Nextpos = _Branpos;
        _Utree_graft_op<_Alnode> _Op(_Getal());

        while (_First != _Last) {
            _Adl_verify_range((*_First).first, (*_First).second);
            auto _UFirst = _Get_unwrapped((*_First).first);
            auto _ULast  = _Get_unwrapped((*_First).second);
            _Op._Append_range_unchecked(_Get_scary()->_Myroot, _UFirst, _ULast);
            _Op._Graft_branch(*_Get_scary(), _Root._Ptr, _Nextpos);
            _First++;
            _Nextpos++;
        }

        _Get_scary()->_Branch_change_pos(_Root._Ptr);
        _Get_scary()->_To_new_end();
        return _Make_iter(_Root._Ptr->branches[_Branpos]);
    }

    template<class _Iter, class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    iterator multiple_graft(_BranIter _Branch, _STD initializer_list<_STD pair<_Iter, _Iter>> _Iterlist) {
        // ghep nhieu nhanh = branch_iterator
        auto _Myroot           = static_cast<const_iterator>(_Branch.get_root());
        branch_size_t _Branpos = static_cast<branch_size_t>(
            _Branch.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));
        return multiple_graft<_Iter>(_Myroot, _Branpos, _Iterlist);
    }

private:
    _Nodeptr _Tree_graft(_Nodeptr _Root, branch_size_t _Pos, unbalanced_tree& _Other) {
        // ghep mot cay khac vao _Root tai _Branpos
        if (this->size() > max_size() - _Other.size()) {
            _Throw_unbalanced_tree_length_error();
        }

        if (this == _STD addressof(_Other) || _Other.empty()) {
            return _Root;
        }

        auto& _Other_data = _Other._Mypair._Myval2;
        auto _Other_root  = _Other_data._Myroot;
        auto _Other_end   = _Other_data._Myend;
#if _ITERATOR_DEBUG_LEVEL == 2
       _Get_scary()->_Adopt_all(_Other_data);
#endif // _ITERATOR_DEBUG_LEVEL == 2

        _Other_end->parent->branches[0] = NULL;
        _Other_end->parent->branches.clear();
        _Other_end->parent = _Other_root;

        _Root->branches.insert(_Root->branches.begin() + _Pos, _Other_root->branches.size(), nullptr);
        for (branch_size_t _Count = 0; _Count < _Other_root->branches.size(); ++_Count) {
            _Root->branches[_Count + _Pos]        = _Other_root->branches[_Count];
            _Other_root->branches[_Count]->parent = _Root;
            _Other_root->branches[_Count]         = NULL;
        }

        _Get_scary()->_Mysize += _STD exchange(_Other_data._Mysize, size_type{0});
        _Get_scary()->_Branch_change_pos(_Root);
        _Get_scary()->_To_new_end();
        _Other_root->branches.clear();
        _Other_root->branches.insert(_Other_root->branches.begin(), _Other_end);
        return _Root->branches[_Pos];
    }

public:
    iterator graft(const_iterator _Root, branch_size_t _Branpos, unbalanced_tree& _Other) {
        // ghep mot cay khac vao _Root tai _Branpos
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "unbalanced tree graft iterator outside range");
        _STL_VERIFY(_Root._Ptr != _Get_scary()->_Myend, "cannot graft branch to end");
        _STL_VERIFY(_Branpos <= _Root._Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_Root._Ptr == _Get_scary()->_Myend->parent) {
            _STL_VERIFY(_Branpos == 0, "graft position for end's parent must be 0");
        }
        return _Make_iter(_Tree_graft(_Root._Ptr, _Branpos, _Other));
    }

    template<class _BranIter, enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    iterator graft(_BranIter _Branch, unbalanced_tree& _Other) {
        // ghep mot cay khac = branch_iterator
        auto _Myroot           = static_cast<const_iterator>(_Branch.get_root());
        branch_size_t _Branpos = static_cast<branch_size_t>(
            _Branch.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));
        return graft(_Myroot, _Branpos, _Other);
    }

    iterator graft(const_iterator _Root, size_type _Branpos, unbalanced_tree&& _Other) {
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "unbalanced tree graft iterator outside range");
        _STL_VERIFY(_Root._Ptr != _Get_scary()->_Myend, "cannot graft branch to end");
        _STL_VERIFY(_Branpos <= _Root._Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_Root._Ptr == _Get_scary()->_Myend->parent) {
            _STL_VERIFY(_Branpos == 0, "graft position for end's parent must be 0");
        }
        return _Make_iter(_Tree_graft(_Root._Ptr, _Branpos, _Other));
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    iterator graft(_BranIter _Branch, unbalanced_tree&& _Other) {
        auto _Myroot           = static_cast<const_iterator>(_Branch.get_root());
        branch_size_t _Branpos = static_cast<branch_size_t>(
            _Branch.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));
        return graft(_Myroot, _Branpos, _STD move(_Other));
    }

public:
    iterator erase(const_iterator _Where) noexcept /* strengthened */ { // xoa mot nut
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Where._Getcont() == _Get_scary(), "unbalanced tree erase iterator outside range");
        _STL_VERIFY(_Where._Ptr != _Get_scary()->_Myroot && _Where._Ptr != _Get_scary()->_Myend, "cannot erase root or end");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        return _Unchecked_erase(_Where._Ptr);
    }

    iterator erase(const_iterator _First, const_iterator _Last) noexcept {
        // xoa [_First, _Last)
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_First._Getcont() == _Get_scary() && _Last._Getcont() == _Get_scary(),
            "unbalanced tree erase iterator outside range");
        _STL_VERIFY(_First._Ptr != _Get_scary()->_Myroot && _First._Ptr != _Get_scary()->_Myend, 
            "cannot erase root or end");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        if (_First._Ptr == begin()._Ptr && _Last._Ptr == _Get_scary()->_Myend) {
            clear();
            return _Make_iter(_Last._Ptr);
        }

        auto _Result = _STD _Prev_iter(_First);
        auto _Erased = _STD _Prev_iter(_Last);
        while (_Erased != _Result) {
            _Unchecked_erase((_Erased--)._Ptr);
        }
        return _Make_iter(_Result._Ptr);
    }

private:
     iterator _Unchecked_erase(const _Nodeptr _Pnode) noexcept { // xoa phan tu tai _Pnode
        iterator _Result(_Pnode, _Get_scary());
        ++_Result;
        _Nodeptr _Parent = _Pnode->parent;
        _Get_scary()->_Orphan_ptr(_Pnode);

        if (_Pnode->branches.size() == 0) {
            _Parent->branches[_Pnode->branpos] = NULL;
            _Parent->branches.erase(_Parent->branches.begin() + _Pnode->branpos);

        } else if (_Pnode->branches[0] == _Get_scary()->_Myend && _Pnode->parent->branches.size() > 1) {
            _Parent->branches[_Pnode->branpos] = NULL;
            _Parent->branches.erase(_Parent->branches.begin() + _Pnode->branpos);
            _Get_scary()->_To_new_end();

        } else { // chuyen tat ca nhanh cho nut cha
            _Parent->branches[_Pnode->branpos] = _Pnode->branches[0];
            _Pnode->branches[0]->parent        = _Parent;

            for (branch_size_t _Idx = 1; _Idx < _Pnode->branches.size(); ++_Idx) {
                _Parent->branches.insert(
                    _Parent->branches.begin() + _Pnode->branpos + _Idx, _Pnode->branches[_Idx]);
                _Pnode->branches[_Idx]->parent = _Parent;
            }
        }

        _Get_scary()->_Mysize--;
        _Get_scary()->_Branch_change_pos(_Parent);
        _Node::_Freenode(_Getal(), _Pnode);
        return _Result;
     }

public:
    void cut(const_iterator _Root, branch_size_t _Branpos) noexcept { // xoa mot nhanh(cay con) _Branpos cua _Root
        if (_Root.bran_size() == 0 || _Root._Ptr == _Get_scary()->_Myend->parent) {
            return;
        }

#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "branch to cut is out of range");
        _STL_VERIFY(_Branpos < _Root._Ptr->branches.size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2
        
        _Unchecked_cut(_Root._Ptr, _Branpos);
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    void cut(_BranIter _Branch) { // xoa mot nhanh(cay con) = brnch_iterator
        auto _Myroot           = static_cast<const_iterator>(_Branch.get_root());
        branch_size_t _Branpos = static_cast<branch_size_t>(
            _Branch.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));
        cut(_Myroot, _Branpos);
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    void cut(_BranIter _First, _BranIter _Last) { // xoa cac nhanh trong [_First, _Last) cua mot nut
        auto _Myroot = static_cast<const_iterator>(_First.get_root());
        if (_Myroot.bran_size() == 0 || _Myroot._Ptr == _Get_scary()->_Myend->parent) {
            return;
        }

#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Myroot._Getcont() == _Get_scary(), "branches to cut is out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        _STD _Adl_verify_range(_First, _Last);
        _Unchecked_range_cut(_First, _Last);
    }          

#define _UNIQUE_POS_CHECK(_Type, _Poslist)                       \
    _Type _Max = _STD max(_Poslist);                             \
    vector<_Type> _Map(_Max + 1, 0);                             \
    auto _UFirst = _Poslist.begin();                             \
    auto _ULast  = _Poslist.end();                               \
    while (_UFirst != _ULast) {                                  \
        _Map[*_UFirst]++;                                        \
        ++_UFirst;                                               \
    }                                                            \
    for (auto& _Count : _Map) {                                  \
        _STL_VERIFY(_Count < 2, "position list must be unique"); \
    }   

    void multiple_cut(const_iterator _Root, _STD initializer_list<branch_size_t> _Poslist) {
       // xoa nhieu nhanh = danh sach vi tri
        if ((_Root.bran_size() == 0 || _Root._Ptr == _Get_scary()->_Myend->parent) && _Poslist.size() == 0) {
            return;
        } else {
            _STL_VERIFY(false, "leaf and end don't have branch");
        }

#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "branches to cut is out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2
     
        _UNIQUE_POS_CHECK(branch_size_t, _Poslist);
        _STD vector<branch_size_t> _Pos(_Poslist);
        auto _First = _Pos.begin();
        auto _Last  = _Pos.end();
        while (_First != _Last) {
            cut(_Root, *_First);
            _Decrease_pos(_STD next(_First), _Last, *_First);
            ++_First;
        }
    }
   
private:
    void _Unchecked_cut(_Nodeptr _Root, branch_size_t _Branpos) noexcept {
        _Nodeptr _Head      = _Root->branches[_Branpos]; 
        _Nodeptr _Lastleaf  = _Head;
        while (_Lastleaf->branches.size() != 0) { // tim nut la cuoi cung cua nhanh      
            _Lastleaf = _Lastleaf->branches.back();
        }
        // neu nut end trong nhanh se xoa, tam thoi ngat lien ket
        bool _End_in_cut = _Lastleaf == _Get_scary()->_Myend;
        if (_End_in_cut) {
            _Lastleaf              = _Lastleaf->parent;
            _Lastleaf->branches[0] = NULL;
            _Lastleaf->branches.clear();
            _Get_scary()->_Myend->parent = NULL;
        }

        iterator _End(_Head, _Get_scary()); 
        iterator _Prev(_Lastleaf, _Get_scary());
        _Head      = NULL;
        _Lastleaf  = NULL;
        _Nodeptr _Erased;
        size_type _Removed = 0;
        while (_Prev != _End) {
            _Erased = (_Prev--)._Ptr;
            _Get_scary()->_Orphan_ptr(_Erased);
            _Node::_Freenode(_Getal(), _Erased);
            ++_Removed;
        }
        
        // _Prev == _End
        _Erased = _Prev._Ptr;
        _Get_scary()->_Orphan_ptr(_Erased);
        _Node::_Freenode(_Getal(), _Erased);
        _Root->branches[_Branpos] = NULL;
        _Root->branches.erase(_Root->branches.begin() + _Branpos);
        _Get_scary()->_Branch_change_pos(_Root);
        _Get_scary()->_Mysize -= (_Removed + 1);
        if (_End_in_cut) {
            _Get_scary()->_To_new_end();
        }
    }

    template<class _BranIter>
    void _Unchecked_range_cut(_BranIter _First, _BranIter _Last) { // remove branch in [_First, _Last)
        auto _Myroot          = static_cast<const_iterator>(_First.get_root());
        branch_size_t _Result = static_cast<branch_size_t>(
            _First.get_branch() - static_cast<typename _BranIter::_Bran_iter>(_Myroot._Ptr->branches.begin()));

        _Nodeptr _Headfirst = *_First;
        _Nodeptr _Lastleaf  = *_STD _Prev_iter(_Last);

        while (_Lastleaf->branches.size() != 0) {
            _Lastleaf = _Lastleaf->branches.back();
        } 
        // neu nut end trong cac nhanh se xoa, tam thoi ngat lien ket
        bool _End_in_cut = _Lastleaf == _Get_scary()->_Myend;
        if (_End_in_cut) {
            _Lastleaf              = _Lastleaf->parent;
            _Lastleaf->branches[0] = NULL;
            _Lastleaf->branches.clear();
            _Get_scary()->_Myend->parent = NULL;
        }

        iterator _End(_Headfirst, _Get_scary()); 
        iterator _Prev(_Lastleaf, _Get_scary());
        _Headfirst = NULL;
        _Lastleaf  = NULL;
        _Nodeptr _Erased;
        size_type _Removed = 0;
        while (_Prev != _End) {     
            _Erased = (_Prev--)._Ptr;
            _Get_scary()->_Orphan_ptr(_Erased);
            _Node::_Freenode(_Getal(), _Erased);
            ++_Removed;
        }

        // _Prev == _End
        _Erased = _Prev._Ptr;
        _Get_scary()->_Orphan_ptr(_Erased);
        _Node::_Freenode(_Getal(), _Erased);
        auto _UFirst = _First;
        while (_UFirst != _Last) {
            *_UFirst = NULL;
            ++_UFirst;
        }    
        _Myroot._Ptr->branches.erase(_First.get_branch(), _Last.get_branch());
        _Get_scary()->_Branch_change_pos(_Myroot._Ptr);
        _Get_scary()->_Mysize -= (_Removed + 1);
        if (_End_in_cut) {
            _Get_scary()->_To_new_end();
        }
    }

    template<class _Iter>
    void _Decrease_pos(_Iter _First, _Iter _Last, const branch_size_t& _Val) {
        // giam tat ca vi tri di 1 neu lon hon _Val
        while (_First != _Last) {
            if (*_First > _Val) {
                (*_First)--;
            }
            ++_First;
        }
    }

public:
    void swap_bran(const_iterator _Where1, branch_size_t _Pos1, const_iterator _Where2, branch_size_t _Pos2) {
        // trao doi nhanh tai _Pos1 cua _Where1 voi nhanh tai _Pos2 cua _Where2 (_Where2 co the thuoc cay khac)
        if (_Where1.bran_size() == 0 || _Where1._Ptr == _Get_scary()->_Myend->parent) {
            return;
        }
         
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Where1._Getcont() == _Get_scary(), "_Where1 out of range");
        _STL_VERIFY(_Pos1 < _Where1.bran_size() && _Pos2 < _Where2.bran_size(), "branch subcript out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        auto _First1 = _Where1.bran_begin() + _Pos1;
        auto _First2 = _Where2.bran_begin() + _Pos2;
        auto _Last1  = _STD _Next_iter(_First1);
        
        if (_Where1._Getcont() == _Where2._Getcont()) {
            if (_Where2.bran_size() == 0 || _Where2._Ptr == _Get_scary()->_Myend->parent) {
                return;
            }
#if _ITERATOR_DEBUG_LEVEL == 2
            _STL_VERIFY((_Where1._Ptr == _Where2._Ptr) 
                || (!_In_bran(_Where1._Ptr, _Where2._Ptr, _Pos1, _Pos1 + 1)
                    && !_In_bran(_Where2._Ptr, _Where1._Ptr, _Pos2, _Pos2 + 1)), 
                "_Where1 is in the swapped branches of _Where2 or vice versa");
#endif // _ITERATOR_DEBUG_LEVEL == 2
            _Local_swap(_First1, _Last1, _First2);
        } else {
            auto _Other_cont = static_cast<_Scary_val*>(const_cast<_STD _Container_base12*>(_Where2._Getcont()));
            if (_Where2.bran_size() == 0 || _Where2._Ptr == _Other_cont->_Myend->parent) {
                return;
            }
            _Swap_with_other_tree(_First1, _Last1, _First2, *_Other_cont);
        }
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    void swap_bran(_BranIter _Bran1, _BranIter _Bran2) {
        // trao doi nhanh = branch_iterator
        auto _My_root    = _Bran1.get_root();
        auto _Other_root = _Bran2.get_root();
        if (_My_root.bran_size() == 0 || _My_root._Ptr == _Get_scary()->_Myend->parent) {
            return;
        }

#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_My_root._Getcont() == _Get_scary(), "the first branch argument out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        auto _First1 = _Bran1;
        auto _First2 = _Bran2;
        auto _Last1  = _STD _Next_iter(_First1); // nem ngoai le neu _First1 la end
        auto _Last2  = _STD _Next_iter(_First2); // nem ngoai le neu _First2 la end

        if (_My_root._Getcont() == _Other_root._Getcont()) {
            if (_Other_root.bran_size() == 0 || _Other_root._Ptr == _Get_scary()->_Myend->parent) {
                return;
            }
            branch_size_t _Lower1 = (*_First1)->branpos;
            branch_size_t _Lower2 = (*_First2)->branpos;

#if _ITERATOR_DEBUG_LEVEL == 2
            _STL_VERIFY((_My_root._Ptr == _Other_root._Ptr) 
                || (!_In_bran(_My_root._Ptr, _Other_root._Ptr, _Lower1, _Lower1 + 1) 
                    && !_In_bran(_Other_root._Ptr, _My_root._Ptr, _Lower2, _Lower2 + 1)),
                "_Bran1 is in _Bran2 or vice versa");
#endif // _ITERATOR_DEBUG_LEVEL == 2

            _Local_swap(_First1, _Last1, _First2);
        } else {
            auto _Other_cont = static_cast<_Scary_val*>(const_cast<_STD _Container_base12*>(_Other_root._Getcont()));
            if (_Other_root.bran_size() == 0 || _Other_root._Ptr == _Other_cont->_Myend->parent) {
                return;
            }
            _Swap_with_other_tree(_First1, _Last1, _First2, *_Other_cont);
        }
    }

    template<class _BranIter, _STD enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    void swap_bran(_BranIter _First1, _BranIter _Last1, _BranIter _First2) {
        // trao doi cac nhanh [_First1, _Last1) voi [_First2, ...)
        if (_First1 == _Last1) {
            return;
        }
        auto _My_root    = _First1.get_root();
        auto _Other_root = _First2.get_root();
        if (_My_root.bran_size() == 0 || _My_root._Ptr == _Get_scary()->_Myend->parent) {
            return;
        }

#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_My_root._Getcont() == _Get_scary(), "the first branch argument out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        auto _Diff = static_cast<branch_size_t>(_Last1 - _First1);
        auto _Save = _First2 + _Diff; // nem ngoai le neu ngoai pham vi

        if (_My_root._Getcont() == _Other_root._Getcont()) {
            if (_Other_root.bran_size() == 0 || _Other_root._Ptr == _Get_scary()->_Myend->parent) {
                return;
            }

#if _ITERATOR_DEBUG_LEVEL == 2
            _STL_VERIFY((_My_root._Ptr == _Other_root._Ptr)
                || (!_In_bran(_My_root._Ptr, _Other_root._Ptr, (*_First1)->branpos, (*_First1)->branpos + _Diff)
                    && !_In_bran(_Other_root._Ptr, _My_root._Ptr, (*_First2)->branpos, (*_First2)->branpos + _Diff)),
                "_Bran1 is in _Bran2 or vice versa");
#endif // _ITERATOR_DEBUG_LEVEL == 2

            _Local_swap(_First1, _Last1, _First2);
        } else {
            auto _Other_cont = static_cast<_Scary_val*>(const_cast<_STD _Container_base12*>(_Other_root._Getcont()));
            if (_Other_root.bran_size() == 0 || _Other_root._Ptr == _Other_cont->_Myend->parent) {
                return;
            }
            _Swap_with_other_tree(_First1, _Last1, _First2, *_Other_cont);
        }
    }

private:
    template<class _BranIter>
    void _Local_swap(_BranIter _First1, _BranIter _Last1, _BranIter _First2) {
        _Adl_verify_range(_First1, _Last1);
        auto _UFirst1      = _First1._Unwrapped();
        auto _UFirst2      = _First2._Unwrapped();
        const auto _ULast1 = _Last1._Unwrapped();

        while (_UFirst1 != _ULast1) {
            _STD swap((*_UFirst1)->parent, (*_UFirst2)->parent);
            _STD iter_swap(_UFirst1, _UFirst2);
            ++_UFirst1;
            ++_UFirst2;
        }

        _Get_scary()->_Branch_change_pos(_First1.get_root()._Ptr);
        _Get_scary()->_Branch_change_pos(_First2.get_root()._Ptr);
        _Get_scary()->_To_new_end();
    }

    template<class _BranIter>
    void _Swap_with_other_tree(_BranIter _First1, _BranIter _Last1, _BranIter _First2, _Scary_val& _Other) {
        _Adl_verify_range(_First1, _Last1);
        auto _UFirst1      = _First1._Unwrapped();
        auto _UFirst2      = _First2._Unwrapped();
        const auto _ULast1 = _Last1._Unwrapped();
        const auto _ULast2 = _UFirst2 + static_cast<branch_size_t>(_ULast1 - _UFirst1);

        _Nodeptr _My_last_leaf    = *(_ULast1 - 1);
        _Nodeptr _Other_last_leaf = *(_ULast2 - 1);

        // neu nut end trong cac nhanh se trao doi, tam thoi ngat lien ket
        while (_My_last_leaf->branches.size() != 0) {
            _My_last_leaf = _My_last_leaf->branches.back();
        }
        if (_My_last_leaf == _Get_scary()->_Myend) {
            _My_last_leaf              = _My_last_leaf->parent;
            _My_last_leaf->branches[0] = NULL;
            _My_last_leaf->branches.clear();
            _Get_scary()->_Myend->parent = NULL;
        }

        while (_Other_last_leaf->branches.size() != 0) {
            _Other_last_leaf = _Other_last_leaf->branches.back();
        }
        if (_Other_last_leaf == _Other._Myend) {
            _Other_last_leaf              = _Other_last_leaf->parent;
            _Other_last_leaf->branches[0] = NULL;
            _Other_last_leaf->branches.clear();
            _Other._Myend->parent = NULL;
        }
   
        // trao doi iterator
        _Nodeptr _My_first_head     = *_UFirst1;
        _Nodeptr _Other_first_head  = *_UFirst2;
        size_type _My_child_size    = 1;
        size_type _Other_child_size = 1;

        iterator _Mynext(_My_last_leaf, _Get_scary());
        iterator _Othernext(_Other_last_leaf, _STD addressof(_Other));
        
        while (_Mynext._Ptr != _My_first_head) {
            _Other._Adopt_ptr(*_Get_scary(), (_Mynext--)._Ptr);
            ++_My_child_size;
        }
        _Other._Adopt_ptr(*_Get_scary(), _My_first_head);

        while (_Othernext._Ptr != _Other_first_head) {
            _Get_scary()->_Adopt_ptr(_Other, (_Othernext--)._Ptr);
            ++_Other_child_size;
        }
        _Get_scary()->_Adopt_ptr(_Other, _Other_first_head);

        // trao doi cac nhanh va parent cua chung
        while (_UFirst1 != _ULast1) {
            _STD swap((*_UFirst1)->parent, (*_UFirst2)->parent);
            _STD iter_swap(_UFirst1, _UFirst2);
            ++_UFirst1;
            ++_UFirst2;
        }
        
        _Get_scary()->_Branch_change_pos(_First1.get_root()._Ptr);
        _Other._Branch_change_pos(_First2.get_root()._Ptr);
        _Get_scary()->_Mysize -= (_My_child_size - _Other_child_size);
        _Other._Mysize        -= (_Other_child_size - _My_child_size);
        _Get_scary()->_To_new_end();
        _Other._To_new_end();
    }

    bool _In_bran(_Nodeptr _Parent, _Nodeptr _Child, branch_size_t _Lower, branch_size_t _Upper) {
        // kiem tra xem _Child co trong cac nhanh tu [_Lower, _Upper) cua nut cha hay khong
        _Nodeptr _Prev = _Child;
        while (_Prev->parent != _Parent && _Prev != _Get_scary()->_Myroot) {
            _Prev = _Prev->parent;
        }
        if (_Prev->parent == _Parent) {
            return _Prev->branpos >= _Upper && _Prev->branpos < _Lower;
        }
        return false;
    }

public:
    template<class _Pr>
    void sort_bran(const_iterator _Root, _Pr _Pred) {
        // sap xep cac nhanh bang gia tri cac nut dau tien cua cac nhanh, su dung _Pred 
#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Root._Getcont() == _Get_scary(), "the root of the branches to be sorted is out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        _STD sort(_Root.bran_begin()._Unwrapped(), _Root.bran_end()._Unwrapped(),
            [&](_Nodeptr _Left, _Nodeptr _Right) { return _Pred(_Left->_Myval, _Right->_Myval); });

        _Get_scary()->_Branch_change_pos(_Root._Ptr);
        _Get_scary()->_To_new_end();
    }

    void sort_bran(const_iterator _Root) {
        // sap xep cac nhanh bang gia tri cac nut dau tien cua cac nhanh, su dung toan tu <
        sort_bran(_Root, _STD less<>());
    }

    template<
        class _BranIter, class _Pr, enable_if_t<_Is_bran_iter<_BranIter, iterator> || _Is_bran_iter<_BranIter, const_iterator>, int> = 0>
    void sort_bran(_BranIter _First, _BranIter _Last, _Pr _Pred) {
        // sap xep cac nhanh trong [_First, _Last) bang gia tri cac nut dau tien cua cac nhanh, su dung _Pred 
        _STD _Adl_verify_range(_First, _Last);
        const auto _Myroot = _First.get_root();

#if _ITERATOR_DEBUG_LEVEL == 2
        _STL_VERIFY(_Myroot._Getcont() == _Get_scary(), "the root of the branches to be sorted is out of range");
#endif // _ITERATOR_DEBUG_LEVEL == 2

        auto _UFirst = _First._Unwrapped();
        auto _ULast  = _Last._Unwrapped();

        _STD sort(_UFirst, _ULast, [&](_Nodeptr _Left, _Nodeptr _Right) { return _Pred(_Left->_Myval, _Right->_Myval); });
        _Get_scary()->_Branch_change_pos(_Myroot._Ptr);
        _Get_scary()->_To_new_end();
    }

    template<class _BranIter>
    void sort_bran(_BranIter _First, _BranIter _Last) {
        // sap xep cac nhanh trong [_First, _Last) bang gia tri cac nut dau tien cua cac nhanh, su dung toan tu < 
        sort_bran(_First, _Last, _STD less<>());
    }

    void swap(unbalanced_tree& _Right) noexcept /* strengthened */ {
        if (this != _STD addressof(_Right)) {
            _STD _Pocs(_Getal(), _Right._Getal());
            _Swap_val(_Right);
        }
    }

private:
    void _Tidy() noexcept {
        auto _Erased  = _STD _Prev_iter(end());
        auto& _Mydata = *_Get_scary();
        while (_Erased._Ptr != _Mydata._Myroot) { 
            _Node::_Freenode(_Getal(), (_Erased--)._Ptr);
        }
        _Orphan_all();
        _Node::_Freenode0(_Getal(), _Mydata._Myroot);
        _Node::_Freenode0(_Getal(), _Mydata._Myend);
    }

public:
    _NODISCARD reference operator[](initializer_list<branch_size_t> _Iloc) noexcept {
        // truy cap den 1 phan tu = danh sach vi tri nhanh, bat dau tu root 
        return *(iterator(_Mypair._Myval2._Myroot, _Get_scary()).to_branch(_Iloc));
    }

    _NODISCARD const_reference operator[](initializer_list<branch_size_t> _Iloc) const noexcept {
        return *(const_iterator(_Mypair._Myval2._Myroot, _Get_scary()).to_branch(_Iloc));
    }

    _NODISCARD reference at(initializer_list<branch_size_t> _Iloc) noexcept {
        return *(iterator(_Mypair._Myval2._Myroot, _Get_scary()).to_branch(_Iloc));
    }

    _NODISCARD const_reference at(initializer_list<branch_size_t> _Iloc) const noexcept {
        return *(const_iterator(_Mypair._Myval2._Myroot, _Get_scary()).to_branch(_Iloc));
    }

    _NODISCARD iterator root() noexcept {
        return iterator(_Mypair._Myval2._Myroot, _Get_scary());
    }

    _NODISCARD const_iterator root() const noexcept {
        return const_iterator(_Mypair._Myval2._Myroot, _Get_scary());
    }

    _NODISCARD iterator begin() noexcept {
        return iterator(_Mypair._Myval2._Myroot->branches.front(), _Get_scary());
    }

    _NODISCARD const_iterator begin() const noexcept {
        return const_iterator(_Mypair._Myval2._Myroot->branches.front(), _Get_scary());
    }

    _NODISCARD iterator end() noexcept {
        return iterator(_Mypair._Myval2._Myend, _Get_scary());
    }

    _NODISCARD const_iterator end() const noexcept {
        return const_iterator(_Mypair._Myval2._Myend, _Get_scary());
    }

    _Unchecked_iterator _Unchecked_root() noexcept {
        return _Unchecked_iterator(_Mypair._Myval2._Myroot, nullptr);
    }

    _Unchecked_const_iterator _Unchecked_root() const noexcept {
        return _Unchecked_const_iterator(_Mypair._Myval2._Myroot, nullptr);
    }

    _Unchecked_iterator _Unchecked_begin() noexcept {
        return _Unchecked_iterator(_Mypair._Myval2._Myroot->branches.front(), nullptr);
    }

    _Unchecked_const_iterator _Unchecked_begin() const noexcept {
        return _Unchecked_const_iterator(_Mypair._Myval2._Myroot->branches.front(), nullptr);
    }

    _Unchecked_iterator _Unchecked_end() noexcept {
        return _Unchecked_iterator(_Mypair._Myval2._Myend, nullptr);
    }

    _Unchecked_const_iterator _Unchecked_end() const noexcept {
        return _Unchecked_const_iterator(_Mypair._Myval2._Myend, nullptr);
    }

    _NODISCARD reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    _NODISCARD const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    _NODISCARD reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    _NODISCARD const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    _NODISCARD const_iterator cbegin() const noexcept {
        return begin();
    }

    _NODISCARD const_iterator cend() const noexcept {
        return end();
    }

    _NODISCARD const_reverse_iterator crbegin() const noexcept {
        return rbegin();
    }

    _NODISCARD const_reverse_iterator crend() const noexcept {
        return rend();
    }

    _NODISCARD size_type size() const noexcept {
        return _Mypair._Myval2._Mysize;
    }

    _NODISCARD size_type max_size() const noexcept {
        return _STD _Min_value(
            static_cast<size_type>((_STD numeric_limits<difference_type>::max)()), _Alnode_traits::max_size(_Getal()));
    }

    _NODISCARD bool empty() const noexcept {
        return _Mypair._Myval2._Mysize == 0;
    }

    _NODISCARD allocator_type get_allocator() const noexcept {
        return static_cast<allocator_type>(_Getal());
    }

private:
    void _Alloc_sentinel_and_proxy() {
        // _GET_PROXY_ALLOCATOR = static_cast<allocator<_Contaner_proxy>>(_Getal())
        // _Container_proxy_ptr<_Alnode> = _Container_proxy_ptr12<allocator<_Container_proxy>>
        // khoi tao _Proxy de cap phat _Myproxy(uy quyen) cho container
        auto&& _Alproxy = _GET_PROXY_ALLOCATOR(_Alnode, _Getal()); 
        _STD _Container_proxy_ptr<_Alnode> _Proxy(_Alproxy, *_Get_scary());
        _Get_scary()->_Myroot              = _Node::_Buyroot(_Getal());
        _Get_scary()->_Myend               = _Node::_Buyend(_Getal());
        _Get_scary()->_Myroot->branches[0] = _Get_scary()->_Myend;
        _Get_scary()->_Myend->parent       = _Get_scary()->_Myroot;
        _Proxy._Release();
    }

    iterator _Make_iter(_Nodeptr _Where) const noexcept {
        return iterator(_Where, _Get_scary());
    }

    const_iterator _Make_const_iter(_Nodeptr _Where) const noexcept {
        return const_iterator(_Where, _Get_scary());
    }

    template <class... _Valty>
    _Nodeptr _Buynode(_CRT_GUARDOVERFLOW branch_size_t _Bransize = 1, _Valty&&... _Val) {
        return _Node::_Buynode(_Getal(), _Get_scary()->_Myroot, _Bransize, _STD forward<_Valty>(_Val)...);
    }

    void _Orphan_all() noexcept {
        _Mypair._Myval2._Orphan_all();
    }

    _Alnode& _Getal() noexcept {
        return _Mypair._Get_first();
    }

    const _Alnode& _Getal() const noexcept {
        return _Mypair._Get_first();
    }

    _Scary_val* _Get_scary() noexcept {
        return _STD addressof(_Mypair._Myval2);
    }

    const _Scary_val* _Get_scary() const noexcept {
        return _STD addressof(_Mypair._Myval2);
    }

    _STD _Compressed_pair<_Alnode, _Scary_val> _Mypair;
};
// unbalanced_tree
template <class _Ty, class _Alloc>
void swap(unbalanced_tree<_Ty, _Alloc>& _Left, unbalanced_tree<_Ty, _Alloc>& _Right) noexcept /* strengthened */ {
    _Left.swap(_Right);
}

template <class _Ty, class _Alloc>
_NODISCARD bool operator==(const unbalanced_tree<_Ty, _Alloc>& _Left, const unbalanced_tree<_Ty, _Alloc>& _Right) {
    if (_Left.size() != _Right.size()) {
        return false;
    }
    auto _UFirst1      = _STD _Get_unwrapped(_Left.begin());
    const auto _ULast1 = _STD _Get_unwrapped(_Left.begin());
    auto _UFirst2      = _STD _Get_unwrapped(_Right.begin());
    for (; _UFirst1 != _ULast1; ++_UFirst1, ++_UFirst2) {
        if ((*_UFirst1 != *_UFirst2) || (_UFirst1->branpos != _UFirst2->branpos)) {
            return false;
        }
    }

    return true;
}

template <class _Ty, class _Alloc>
_NODISCARD bool operator!=(const unbalanced_tree<_Ty, _Alloc>& _Left, const unbalanced_tree<_Ty, _Alloc>& _Right) {
    return !(_Left == _Right);
}

template <class _Ty, class _Alloc>
_NODISCARD bool operator<(const unbalanced_tree<_Ty, _Alloc>& _Left, const unbalanced_tree<_Ty, _Alloc>& _Right) {
    return _STD lexicographical_compare(_Left.begin(), _Left.end(), _Right.begin(), _Right.end());
}

template <class _Ty, class _Alloc>
_NODISCARD bool operator>(const unbalanced_tree<_Ty, _Alloc>& _Left, const unbalanced_tree<_Ty, _Alloc>& _Right) {
    return _Right < _Left;
}

template <class _Ty, class _Alloc>
_NODISCARD bool operator<=(const unbalanced_tree<_Ty, _Alloc>& _Left, const unbalanced_tree<_Ty, _Alloc>& _Right) {
    return !(_Right < _Left);
}

template <class _Ty, class _Alloc>
_NODISCARD bool operator>=(const unbalanced_tree<_Ty, _Alloc>& _Left, const unbalanced_tree<_Ty, _Alloc>& _Right) {
    return !(_Left < _Right);
}

#pragma pop_macro("new")
_STL_RESTORE_CLANG_WARNINGS
#pragma warning(pop)
#pragma pack(pop)
#endif // _STL_COMPILER_PREPROCESSOR
#endif // _UNBALANCED_TREE_
