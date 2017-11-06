; I took most of this from Matt Might's:
; http://matt.might.net/articles/lexers-in-racket/
#lang racket
(require parser-tools/lex)
(require (prefix-in : parser-tools/lex-sre))

;(struct char (c) #:)

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

(define ab-test-in (open-input-string "abbaa")) ;"1 + 2 * 3 + 4 * 1 + 3")); , aabbaa
      
(define (next-tok)
  (lex ab-test-in))

(define curtok (next-tok))

(define (accept c)
  (if (not (equal? curtok c))
      (raise 'unexpected-token)
      (begin
        (printf "Accepting ~a\n" c)
        (set! curtok (next-tok)))))

; S -> A 'eof | B 'eof
(define (parse-S)
  (match curtok
    [#\a
     ; ^ A 'eof
     (parse-A)
     ; A ^ 'eof
     (accept 'eof)]
    [#\b
     ; ^ B 'eof
     (parse-B)
     ; B ^ 'eof
     (accept 'eof)]))

; A -> aAa | B
(define (parse-A)
  (match curtok
    ; ^ aAa
    [#\a
     (begin
       (accept #\a)
       ; a ^ A a
       (parse-A)
       ; a A ^ a
       (accept #\a))]
       ; a A a ^ ...
    [#\b
     ; ^ b b 
     (parse-B)]))

; B -> ^ b b
(define (parse-B)
  (begin
    ; ^ b b
    (accept #\b)
    ; b ^ b
    (accept #\b)
    ; b b ^
    ))

(define (accept-number)
  (if (number? curtok)
      (accept curtok)
      (raise 'unexpected-token)))

; Add -> Term MoreTerms
(define (parse-Add)
  ; ^ Term MoreTerms
  (parse-Term)
  ; Term ^ MoreTerms
  (parse-MoreTerms)
  ; Term MoreTerms ^
  )

; MoreTerms -> + Term MoreTerms | epsilon
(define (parse-MoreTerms)
  (match curtok
    ['plus
     ; + Term MoreTerms
     (begin
       (accept 'plus)
       (parse-Term)
       (parse-MoreTerms))]
    ['eof
     (void)]))

; Term -> num MoreNums
(define (parse-Term)
  (accept-number)
  ; num ^ MoreNums
  (parse-MoreNums)
  ; num MoreNums
  )

; MoreNums -> * num MoreNums | epsilon
(define (parse-MoreNums)
  (match curtok
    ['times
     ; ^ * num MoreNums
     (accept 'times)
     ; * ^ num MoreNums
     (accept-number)
     ; * num ^ MoreNums
     (parse-MoreNums)
     ; * num MoreNums ^
     ]
    ['plus
     (void)]
    ['eof
     (void)]))
     





     






