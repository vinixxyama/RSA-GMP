//Vinicius Yamamoto	RA:490105

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <math.h>

mpz_t n; 	// modulo n
mpz_t e; 	// expoente publica
mpz_t d; 	// expoente privada
mpz_t p; 	// prime p
mpz_t q; 	// prime q
mpz_t n; 	//modulo
mpz_t e;	//expoente

void segundaparte(){
	mpz_t phi;
	mpz_t randon;
	mpz_t aux;
	mpz_t p_1; //p-1
	mpz_t q_1; //q-1
	mpz_t res_decripto; 
	mpz_t res_cripto;
	mpz_t textoentra;
	mpz_t mask;
	mpz_t rop;
	gmp_randstate_t state;
	int tamanhochave;
	int esc;

	mpz_inits(textoentra);
	mpz_inits(aux);
	mpz_inits(n);
	mpz_inits(e);
	mpz_inits(d);
	mpz_inits(p);
	mpz_inits(q);
	mpz_inits(phi);
	mpz_inits(randon);
	mpz_inits(res_cripto);
	mpz_inits(res_decripto);
	mpz_inits(p_1);
	mpz_inits(q_1);
	mpz_inits(mask);
}


int main(){
	mpz_t phi;
	mpz_t randon;
	mpz_t aux;
	mpz_t p_1; //p-1
	mpz_t q_1; //q-1
	mpz_t res_decripto; 
	mpz_t res_cripto;
	mpz_t textoentra;
	mpz_t mask;
	mpz_t rop;
	gmp_randstate_t state;
	int tamanhochave;
	int esc;

	mpz_inits(textoentra);
	mpz_inits(aux);
	mpz_inits(n);
	mpz_inits(e);
	mpz_inits(d);
	mpz_inits(p);
	mpz_inits(q);
	mpz_inits(phi);
	mpz_inits(randon);
	mpz_inits(res_cripto);
	mpz_inits(res_decripto);
	mpz_inits(p_1);
	mpz_inits(q_1);
	mpz_inits(mask);

	int prouse=0;

	printf("Qual quer testar");
	scanf("%d", &prouse);

	if(prouse == 1){
		printf("tamanho da chave:\n");
	  	scanf("%d", &tamanhochave);

	  	gmp_randinit_default(state);
		//GERA P
		mpz_urandomb(randon, state, tamanhochave/2);
		mpz_nextprime(p, randon);
		//GERA Q
		mpz_urandomb(randon, state, tamanhochave/2);
		mpz_nextprime(q, randon);

		//N = P*Q
		mpz_mul(n,p,q);
		// φ(n) = (p-1)(q-1)
		mpz_sub_ui(p_1, p, 1);
		mpz_sub_ui(q_1, q, 1);
		mpz_mul(phi, q_1, p_1);

	    gmp_printf("P:%Zd\nQ:%Zd\n", p, q);

		mpz_set(aux, phi);
	  	mpz_nextprime(aux, aux);

	  	gmp_randinit_default(state);
	  	//Encontra um e que o gcd de phi e 1
	  	while(mpz_gcd(p_1, e, phi), mpz_cmp_ui(p_1, 1) != 0){
	    	mpz_urandomm(e, state, phi);
	  	}
		mpz_gcdext(p_1, aux, mask, phi, e);	
		mpz_set(d, mask);
		gmp_printf("PHI: %Zd\n", phi);
		gmp_printf("MODULO: %Zd\n", n);
	}else{
		printf("tamanho da chave:\n");
	  	scanf("%d", &tamanhochave);

	  	gmp_randinit_default(state);
		//GERA P
		mpz_urandomb(randon, state, tamanhochave/2);
		mpz_nextprime(p, randon);
		//GERA Q
		mpz_urandomb(randon, state, tamanhochave/2);
		mpz_nextprime(q, randon);

		mpz_set(aux, phi);
	  	mpz_nextprime(aux, aux);

	  	gmp_randinit_default(state);
	  	//Encontra um e que o gcd de phi e 1

	  	printf("base:\n");
		scanf("%d", &esc);
		if(esc == 10){
			printf("Moduclo:\n");
			gmp_scanf("%Zd", n);
			printf("chave publica:\n");
			gmp_scanf("%Zd", e);
			
			mpz_gcdext(p_1, aux, mask, phi, e);	
			mpz_set(d, mask);
			gmp_printf("expoente privado: %Zd\n", d);
			printf("mensagem:\n");
	  		gmp_scanf("%Zd",textoentra);
		}else if(esc == 16){
			printf("Moduclo:\n");
			gmp_scanf("%Zx", n);
			printf("chave publica:\n");
			gmp_scanf("%Zx", e);
			
			mpz_gcdext(p_1, aux, mask, phi, e);	
			mpz_set(d, mask);
			gmp_printf("expoente privado: %Zx\n", d);	
			printf("mensagem:\n");
	  		gmp_scanf("%Zx",textoentra);
		}

		//Criptografa
		mpz_mod(textoentra, textoentra, n);
		mpz_init(mask);
		mpz_init(rop);
		mpz_set_ui(mask,1);

		mpz_set_ui(res_cripto,1);
		while(mpz_cmp_ui(e,0) > 0){
			mpz_and(rop, e, mask);
			if(mpz_cmp_ui(rop, 1) == 0){
			  mpz_mul(res_cripto,res_cripto,textoentra);
			  mpz_mod(res_cripto,res_cripto,n);
			}
			mpz_mul(textoentra,textoentra,textoentra);
			mpz_mod(textoentra,textoentra,n);

			mpz_tdiv_q_2exp(e, e,1);
		}
		//Decriptografa
		mpz_mod(res_cripto, res_cripto, n);
		mpz_init(mask);
		mpz_init(rop);
		mpz_set_ui(mask,1);

		mpz_set_ui(res_decripto,1);
		while(mpz_cmp_ui(d,0) > 0){
			mpz_and(rop, d, mask);
			if(mpz_cmp_ui(rop, 1) == 0){
			  mpz_mul(res_decripto,res_decripto,res_cripto);
			  mpz_mod(res_decripto,res_decripto,n);
			}
			mpz_mul(res_cripto, res_cripto, res_cripto);
			mpz_mod(res_cripto, res_cripto ,n);

			mpz_tdiv_q_2exp(d, d,1);
		}
		if(esc == 10){
			printf("Mensagem Criprografada \n");
		    gmp_printf("%Zd\n", res_cripto);
		    printf("Mensagem Decriptografada\n");
		    gmp_printf("%Zd\n", res_decripto);
		}else if(esc == 16){
			printf("Mensagem Criprografada \n");
		    gmp_printf("%Zx\n", res_cripto);
		    printf("Mensagem Decriptografada\n");
		    gmp_printf("%Zx\n", res_decripto);
		}
	}
}