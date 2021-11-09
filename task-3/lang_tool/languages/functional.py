import random
from enum import Enum
from typing import List, Optional

from lang_tool.languages.base import BaseLanguage
from lang_tool.common.exceptions import NotEnoughTokensError, TooManyTokensError


class Typing(Enum):
    STRICT = '0'
    DYNAMIC = '1'


class FunctionalLanguage(BaseLanguage):
    def __init__(self):
        super().__init__()
        self._typing: Optional[Typing] = None
        self._support_lazy_calculations: Optional[bool] = None

    def __repr__(self):
        return f"It is Functional language: name = {self.name} ({self.rating}% | {self.year_created}), " \
               f"typing = {self.typing.name}, lazy calculations = {str(self.support_lazy_calculations).lower()}. " \
               f"year / name.size() = {self.year_div_name_len:.3f}"

    @property
    def typing(self):
        return self._typing

    @typing.setter
    def typing(self, value):
        self._typing = Typing(value)

    @property
    def support_lazy_calculations(self):
        return self._support_lazy_calculations

    @support_lazy_calculations.setter
    def support_lazy_calculations(self, value):
        if value == '0':
            self._support_lazy_calculations = False
        elif value == '1':
            self._support_lazy_calculations = True
        else:
            raise ValueError(f"Lazy calculations support expected to be 0 or 1, but \"{value}\" is not")

    def fill_randomly(self):
        super().fill_randomly()
        self._typing = random.choice([Typing.STRICT, Typing.DYNAMIC])
        self._support_lazy_calculations = bool(random.randint(0, 1))

    def fill_from_tokens(self, tokens: List[str]):
        """Заполняет информацию о функциональном ЯП

        :raises ValueError: при некорректном значении типизации или флага поддержки ленивых вычислений
        :raises NotEnoughTokensError: при недостаточном количестве параметров
                                      (динамическая/статическая типизация, поддержка ленивых вычислений)
        :raises TooManyTokensError: при наличии лишних параметров помимо двух
                                    (динамическая/статическая типизация, поддержка ленивых вычислений)
        """
        if len(tokens) == 0:
            raise NotEnoughTokensError("For functional language, it is necessary to have flags (0/1): "
                                       "dynamic (1) or static (0) typing, lazy calculations support")
        elif len(tokens) == 1:
            raise NotEnoughTokensError("For functional language, it is necessary to have flag (0/1): "
                                       "lazy calculations support")
        elif len(tokens) == 2:
            self.typing = tokens[0]
            self.support_lazy_calculations = tokens[1]
        else:
            raise TooManyTokensError("For functional language, it is necessary to have exactly 2 flags: "
                                     "dynamic (1) or static (0) typing, lazy calculations support")
