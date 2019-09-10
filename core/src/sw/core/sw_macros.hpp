//
// Created by Ilya on 30.06.2019.
//

#ifndef SANDWICH_SW_MACROS_HPP
#define SANDWICH_SW_MACROS_HPP

#define REMOVE_DEFAULTS(t)        \
t(const t &) = delete;            \
t(t &&) = delete;                 \
t &operator=(const t &) = delete; \
t &operator=(t &&) = delete;

#endif //SANDWICH_SW_MACROS_HPP
