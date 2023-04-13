import random
from typing import List, Optional

from lang_tool.languages.base import BaseLanguage
from lang_tool.common.exceptions import NotEnoughTokensError, TooManyTokensError

class ProcedureLanguage(BaseLanguage):
    def __init__(self):
        super().__init__()
        self._support_abstract_types: Optional[bool] = None

    def __repr__(self):
        return f"It is Procedure language: name = {self.name} ({self.rating}% | {self.year_created}), " \
               f"abstract types support = {str(self.support_abstract_types).lower()}. " \
               f"year / name.size() = {self.year_div_name_len:.3f}"

    @property
    def support_abstract_types(self):
        return self._support_abstract_types

    @support_abstract_types.setter
    def support_abstract_types(self, value):
        if value == '0':
            self._support_abstract_types = False
        elif value == '1':
            self._support_abstract_types = True
        else:
            raise ValueError(f"Abstract types support expected to be 0 or 1, but \"{value}\" is not")

    def fill_randomly(self):
        super().fill_randomly()
        self._support_abstract_types = bool(random.randint(0, 1))

    def fill_from_tokens(self, tokens: List[str]):
        """Заполняет информацию о процедурном ЯП

        :raises ValueError: при некорректном значении типизации или флага поддержки ленивых вычислений
        :raises NotEnoughTokensError: при недостаточном количестве токенов
                                      (поддержка абстрактных типов)
        :raises TooManyTokensError: при наличии лишних параметров помимо одного
                                    (поддержка абстрактных типов)
        """
        if len(tokens) == 0:
            raise NotEnoughTokensError("For procedure language, it is necessary to have flag (0/1): "
                                       "abstract types support")
        elif len(tokens) == 1:
            self.support_abstract_types = tokens[0]
        else:
            raise TooManyTokensError("For procedure language, it is necessary to have exactly 1 flag (0/1): "
                                     "abstract types support")
