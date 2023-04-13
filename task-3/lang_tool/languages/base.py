import random
from string import hexdigits
from typing import Optional, Union

DEFAULT_LENGTH = 20
MIN_YEAR = 1970
MAX_YEAR = 5999
MIN_RATING = 0
MAX_RATING = 25


def random_string(length: int = DEFAULT_LENGTH):
    """Случайная строка заданной длины

    :param length: длина строки, по умолчанию DEFAULT_LENGTH=20
    """
    result_str = ''.join(random.choice(hexdigits) for _ in range(length))
    return result_str


class BaseLanguage:
    """Базовый класс языка программирования"""
    def __init__(self):
        """Конструктор базового класса ЯП, создаёт поля и заполняет их None"""
        self._name: Optional[str] = None
        self._year_created: Optional[int] = None
        self._rating: Optional[Union[float, int]] = None

    @property
    def year_div_name_len(self) -> float:
        """Частное от деления года создания на количество символов в названии"""
        return self.year_created / len(self.name)

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        """Устанавливает значение имени ЯП

        :param value: новое значение

        :raises ValueError: если новое значение пустая строка
        """
        if value:
            self._name = value
        else:
            raise ValueError(f"Name excepted to be non-empty string, but input empty")

    @property
    def year_created(self):
        return self._year_created

    @year_created.setter
    def year_created(self, value):
        """Устанавливает значение года создания

        :param value: новое значение

        :raises ValueError: если новое значение не целое число
        """
        if value.isdigit():
            self._year_created = int(value)
        else:
            raise ValueError(f"Year created excepted to be positive integer, but \"{value}\" is not")

    @property
    def rating(self):
        return self._rating

    @rating.setter
    def rating(self, value):
        """Устанавливает значение рейтинга TIOBE

        :param value: новое значение

        :raises ValueError: если новое значение не дробное число
        """
        try:
            self._rating = float(value)
        except ValueError:
            raise ValueError(f"TIOBE rating excepted to be float, but \"{value}\" is not")

    def fill_randomly(self):
        """Рандомное заполнение информации о ЯП"""
        self.name = random_string()
        self._year_created = random.randint(MIN_YEAR, MAX_YEAR)
        self._rating = random.randrange(MIN_RATING, MAX_RATING)
