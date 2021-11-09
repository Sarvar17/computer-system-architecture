import random
from enum import Enum
from typing import List, Optional

from lang_tool.languages.base import BaseLanguage
from lang_tool.common.exceptions import NotEnoughTokensError, TooManyTokensError


class Inheritance(Enum):
    SINGLE = '0'
    MULTIPLE = '1'
    INTERFACE = '2'


class ObjectOrientedLanguage(BaseLanguage):
    def __init__(self):
        super().__init__()
        self._inheritance: Optional[Inheritance] = None

    def __repr__(self):
        return f"It is Object-oriented language: name = {self.name} ({self.rating}% | {self.year_created}), " \
               f"inheritance = {self.inheritance.name}. year / name.size() = {self.year_div_name_len:.3f}"

    @property
    def inheritance(self):
        return self._inheritance

    @inheritance.setter
    def inheritance(self, value):
        self._inheritance = Inheritance(value)

    def fill_randomly(self):
        super().fill_randomly()
        self._inheritance = random.choice([Inheritance.SINGLE, Inheritance.MULTIPLE, Inheritance.INTERFACE])

    def fill_from_tokens(self, tokens: List[str]):
        """Заполняет информацию о процедурном ЯП

        :raises ValueError: при некорректном значении типизации или флага поддержки ленивых вычислений
        :raises NotEnoughTokensError: при недостаточном количестве токенов
                                      (поддержка абстрактных типов)
        :raises TooManyTokensError: при наличии лишних параметров помимо одного
                                    (тип наследования: SINGLE=0, MULTIPLE=1, INTERFACE=2)
        """
        if len(tokens) == 0:
            raise NotEnoughTokensError("For procedure language, it is necessary to have abstract types "
                                       "support value: 0/1/2 (SINGLE=0, MULTIPLE=1, INTERFACE=2)")
        elif len(tokens) == 1:
            self.inheritance = tokens[0]
        else:
            raise TooManyTokensError("For procedure language, it is necessary to have abstract types "
                                     "support value: 0/1/2 (SINGLE=0, MULTIPLE=1, INTERFACE=2)")
