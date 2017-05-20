// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <utility>

namespace vrm
{
    namespace impl
    {
        template <typename...>
        struct overload_set;

        template <typename TF>
        struct overload_set<TF> : TF
        {
            using call_type = TF;
            using call_type::operator();

            inline overload_set(TF&& f) noexcept : TF(std::forward<TF>(f))
            {
            }
        };

        template <typename TF, typename... TFs>
        struct overload_set<TF, TFs...> : TF, overload_set<TFs...>::call_type
        {
            using base_type = typename overload_set<TFs...>::call_type;

            using f_type = TF;
            using call_type = overload_set;

            inline overload_set(TF &&f, TFs &&... fs) noexcept
                : f_type(std::forward<TF>(f)),
                  base_type(std::forward<TFs>(fs)...)
            {
            }

            using f_type::operator();
            using base_type::operator();
        };
    }

    template <typename... TFs>
    inline auto make_overload(TFs && ... fs) noexcept
    {
        return impl::overload_set<TFs...>{std::forward<TFs>(fs)...};
    }
}
