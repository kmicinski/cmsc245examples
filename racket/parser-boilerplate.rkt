; I took most of this from Matt Might's:
; http://matt.might.net/articles/lexers-in-racket/
#lang racket
(require parser-tools/lex)
(require (prefix-in : parser-tools/lex-sre))

; Our lexer, on which we will expand for class
(define lex
 (lexer
    ; skip spaces:
    [#\space     (lex input-port)]
    ; skip newline:
    [#\newline   (lex input-port)]

    [#\+         'plus]
    [#\-         'minus]
    [#\*         'times]
    [#\/         'div]

    [(:: (:? #\-) (:+ (char-range #\0 #\9))) (string->number lexeme)]
    ; an actual character:
    [any-char    (string-ref lexeme 0)]))

; Test input channel
(define ab-test-in (open-input-string "abba")) ; Whatever test string you want here...

; Get the next token
(define (next-tok)
  (lex ab-test-in))

; This is the current token
(define curtok (next-tok))

; Accept a token c, or else fail with an exception 'unexpected-token
(define (accept c)
  (if (not (equal? curtok c))
      (raise 'unexpected-token)
      (begin
        (printf "Accepting ~a\n" c)
        (set! curtok (next-tok)))))

; A -> aAa | B
; B -> bb

; ^ A
(define (parse-A)
  (match curtok
    [#\a
     (begin
       ; ^ aAa
       (accept #\a)
       ; a ^ Aa
       (parse-A)
       ; a A ^ a
       (accept #\a))]
    ; ^ bb
    [#\b (parse-B)]))

; ^ B
(define (parse-B)
  (begin
    ; ^ bb
    (accept #\b)
    ; b ^ b
    (accept #\b)
    ; bb ^
    (void)))
