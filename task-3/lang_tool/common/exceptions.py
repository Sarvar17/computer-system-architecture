class ParseError(Exception):
    pass


class NotEnoughTokensError(ParseError):
    pass


class TooManyTokensError(ParseError):
    pass
